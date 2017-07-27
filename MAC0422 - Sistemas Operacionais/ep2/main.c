#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "cyclist.h"
#include "speedway.h"
#include "team.h"

int gameEnded;
int N; 					// número de ciclistas (validar que > 4)
int D; 					// tamanho da pista (validar que > 249)
int RUN_TYPE; 	// tipo de velocidade (0 é constante, 1 é randomica) TODO: enumerar isso
int max_lap = 0;
int max_lap_updated = 0;
int last_cyclist_removed = -1;
int debug = 0;
int last_printed_lap_a = 0;
int last_printed_lap_b = 0;
int winner = 0;
Cyclist **cyclists;
Team *team_a;
Team *team_b;
Speedway *pista;

pthread_mutex_t mutex_max_lap;

pthread_barrier_t first_barrier, second_barrier, second_barrier_alt;
pthread_barrier_t *cur_second_barrier;

double myRandom () {
	return (double) rand() / (double) ((unsigned) RAND_MAX + 1);
}

void swap (Cyclist **a, Cyclist **b) {
	Cyclist *c = *a;
	*a = *b;
	*b = c;
}

// Debug
void printAll () {
	printf ("\nTime A:\n");
	team_print (team_a, N);
	printf ("\n\nTime B:\n");
	team_print (team_b, N);
	printf ("\n");
}

void printLap(int t, int lap) {
	Team *p = t == 0 ? team_a : team_b;
	printf("Equipe %d finalizou a volta %d no tempo %dms.\n", t, lap, p->cyclists[2]->time);
	for (int i = 0; i < 3; i++) {
		cyclist_print (p->cyclists[i]);
	}
	printf ("\n");
}

void printDebug() {
	for (int i = 0; i < pista->n; i++) {
		printf("Posição: %d\t", i);
		for (int j = 0; j < 2; j++) {
			printf("[ vaga %d: ", j+1);
			if (pista->slots[i]->cyclists[j] == NULL) {
				printf("vazio ]");
			} else {
				printf("ID %d ]", pista->slots[i]->cyclists[j]->i);
			}

			if (j == 0) printf (" | ");
		}
		printf ("\n");
	}
}

void updateMaxLap (int new_max_lap) {
	pthread_mutex_lock (&mutex_max_lap);
	if (new_max_lap > max_lap) {
		max_lap = new_max_lap;
		max_lap_updated = 1;
	}
	pthread_mutex_unlock (&mutex_max_lap);
}

void resetMaxLapFlag () {
	pthread_mutex_lock (&mutex_max_lap);
	max_lap_updated = 0;
	pthread_mutex_unlock (&mutex_max_lap);
}

void sortPista (Team *team) {
	for (int i = 0; i < (team->n - 1); i++) {
		if (team->cyclists[i]->position < team->cyclists[i+1]->position)
			swap(&(team->cyclists[i]), &(team->cyclists[i+1]));
	}
}

void updatePositions () {
	sortPista (team_a);
	sortPista (team_b);
}

int removeCyclistFromTeam (Team *team) {
	// Sorteia um ciclista para quebrar
	int index = (int) floor (myRandom () * team->n);

	// Obtem o ciclista sorteado
	Cyclist *this = team->cyclists[index];
	int i = this->i;
	float constant = this->team * (D / 2.0); // If team 1, then sum half of the speedway

	// Calcula qual volta e posição da volta ele quebrou
	int lap = (int) this->position / D;
	float pos = this->position - lap * D;

	// Imprime a informação do ciclista quebrado
	printf ("O ciclista %d quebrou na posição %f da volta %d.\n", this->i, pos, lap);

	// Atualiza a informação de qual volta ele quebrou
	this->broken_at_lap = lap;

	// Remove ele da pista
	speedway_removeCyclist (pista, this, this->position + constant);

	// Remove o ciclista do vetor do seu time
	for (int j = index; j < (team->n - 1); j++) {
		//printf ("[TESTE] (n: %d) Swappando %d com %d\n", team->n, j, j+1);
		swap (&(team->cyclists[j]), &(team->cyclists[j+1]));
	}
	//printf ("[TESTE] Antes tinha %d membros.\n", team->n);
	team->n -= 1;
	//printf ("[TESTE] Agora tem %d membros.\n", team->n);

	// Retorna o identificador do ciclista quebrado
	return i;
}

// Computa a probabilidade de 10%, remove um ciclista e retorna o id dele
int tryToRemoveCyclist () {
	double p = myRandom ();
	int n = team_a->n + team_b->n;

	if (p < 0.1 && n > 6) {
		int m = (int) floor (myRandom () * n);

		if (team_b->n <= 3 || (team_a->n > 3 && m < team_a->n)) return removeCyclistFromTeam (team_a);
		else return removeCyclistFromTeam (team_b);
	}

	return -1;
}

void updateCyclistsVelocity () {
	// "Se a velocidade sorteada para um ciclista for de 30Km/h, todos os ciclistas companheiros de equipe que
	// estiverem atrás dele, naquela volta, devem pedalar a 30Km/h, independente do valor que foi sorteado para eles"
	int flag = 0;

	for (int i = 0; i < 2; i++) {
		Team *team = i == 0 ? team_a : team_b;
		int cur_lap = max_lap;

		for (int j = 0; j < team->n; j++) {
			Cyclist *this = team->cyclists[j];

			int this_lap = ((int) this->position) / D;
			if (this_lap < cur_lap) {
				flag = 0;
				cur_lap = this_lap;
			}

			float t = myRandom ();

			if (flag != 0) {
				this->speed = 30;

			} else if (t < 0.5)  {
				if (this->speed == 60) {
					flag = 1;
				}
				this->speed = 30;

			} else {
				this->speed = 60;

			}
		}
	}
}

int isGameEnded () {
	// Identificamos o vencedor no momento da vitoria
	// evita que haja uma ultrapassagem até que o último de cada time chegue
	if (winner == 0) {
		if (team_a->cyclists[2]->position > 16 * D) winner += 1;
		if (team_b->cyclists[2]->position > 16 * D) winner += 2;
	}

	// Se todos ciclistas passaram a lista de chegada, retorna a vitoria antes computada
	if (team_a->cyclists[team_a->n - 1]->position > 16 * D && team_b->cyclists[team_b->n - 1]->position > 16 * D) {
		return winner;
	}

	// Verifica caso de 3o ciclista de uma equipe ultrapassar o 3o ciclista da outra
	if (team_a->cyclists[2]->position > team_b->cyclists[2]->position + (D / 2.0)) return 1;
	else if (team_b->cyclists[2]->position > team_a->cyclists[2]->position + (D / 2.0)) return 2;

	return 0;
}

void *run (void *cyclist) {
	Cyclist *this = (Cyclist *) cyclist;
	float constant = this->team * (D / 2.0); // If team 1, then sum half of the speedway

	// Se ele ainda não ultrapassou a linha de chegada, soma tempo de corrida
	if (this->position <= 16 * D) {
		this->time += 60;
	}

	// Update cyclist's position
	this->position += (float) this->speed / 60.0;

	// Nova posição no vetor
	int new_pos = ((int) (this->position + constant)) % D;

	if (new_pos != this->vector_position) {
		// Try to insert cyclist into new position
		int tryInsert = speedway_insertCyclist (pista, this, this->position + constant);

		if (tryInsert > 0) {
			// Insertion went ok
			// Remove cyclist from old position
			speedway_removeCyclist (pista, this, this->position + constant - ((float) this->speed / 60.0));

			if (new_pos < this->vector_position) {
				updateMaxLap (((int) this->position) / D);
			}

			this->vector_position = new_pos;

		} else {
			// Insertion failed. Let's return to old position
			// Update cyclist's position
			this->position -= (float) this->speed / 60.0;

		}
	}

	// NOTE falar na apresentação
	int x = pthread_barrier_wait (&first_barrier);

	if (x != 0) {
		// Atualiza as posições nos vetores equipe_a e equipe_b
		updatePositions ();

		// Se o terceiro ciclista tiver acabado uma volta imprimir
		int lap_tmp = ((int) team_a->cyclists[2]->position) / D;
		if (lap_tmp > last_printed_lap_a) {
			last_printed_lap_a = lap_tmp;
			printLap (0, last_printed_lap_a);
		}

		lap_tmp = ((int) team_b->cyclists[2]->position) / D;
		if (lap_tmp > last_printed_lap_b) {
			last_printed_lap_b = lap_tmp;
			printLap (1, last_printed_lap_b);
		}

		if (max_lap_updated) {
			// Se for uma volta multiplo de 4 e maior que zero, tenta tirar um ciclista
			if (max_lap % 4 == 0 && max_lap > 0) {
        last_cyclist_removed = tryToRemoveCyclist ();

				// Checa se algum ciclista foi removido
				if (last_cyclist_removed >= 0) {
					// Cria a próxima barreira para alterna-las no futuro, visto que temos um ciclista a menos
					// TODO: verificar se barreira foi criadas corretamente, sem erro
					pthread_barrier_destroy (&first_barrier);
					pthread_barrier_init (&first_barrier, NULL, team_a->n + team_b->n);

					pthread_barrier_t *other_barrier;
					if (cur_second_barrier == &second_barrier) {
						other_barrier = &second_barrier_alt;
					} else {
						other_barrier = &second_barrier;
					}

					// TODO: verificar se barreira foi criadas corretamente, sem erro
					pthread_barrier_destroy (other_barrier);
					pthread_barrier_init (other_barrier, NULL, team_a->n + team_b->n);
				}

    	} else {
				last_cyclist_removed = -1;

			}

			// Se for volta com velocidades randomicas, então atualiza as velocidades
			if (RUN_TYPE != 0) {
        updateCyclistsVelocity ();
      }
		}

		// Debug a cada 60ms
		if (debug) {
			printDebug ();
			printf ("\n");
		}

		// Reseta a flag "max_lap_updated"
		resetMaxLapFlag (); // reseta a flag

		gameEnded = isGameEnded ();
		if (gameEnded > 0) {
			printAll ();

			printf ("Corrida acabou!\n");
			if (gameEnded == 1) printf ("Equipe A ganhou.\n");
			else if (gameEnded == 2) printf ("Equipe B ganhou.\n");
			else if (gameEnded == 3) printf ("Empate.\n");
    }
	}

	// NOTE falar na apresentação
	x = pthread_barrier_wait (cur_second_barrier);

	if (gameEnded == 0) {
		// Alternate second barrier
		if (x != 0 && last_cyclist_removed != -1) {
			// Um ciclista foi removido, então alterna a barreira
			if (cur_second_barrier == &second_barrier) {
				cur_second_barrier = &second_barrier_alt;
			} else {
				cur_second_barrier = &second_barrier;
			}

			last_cyclist_removed = -1;
		}

		if (this->i != last_cyclist_removed) {
			// Run again
			return run (this);
	
		}
	}

	if (debug) {
		printf ("DEBUG: Destruindo a thread do ciclista %d.\n", this->i);
	}

	return NULL;
}

void wrongUsage () {
	printf("usage: ep2 <D> <N> <run type> <debug>\n\n");
	printf("- D -- length of speedway (must be bigger than 249).\n");
	printf("- N -- number of cyclists in each team (must be bigger than 4).\n");
	printf("- run type -- 'u' for constant speed and 'v' for random speed.\n");
	printf("- debug -- 'd' for debug mode and nothing for normal mode.\n");
	exit (-1);
}

int main (int argc, char *argv[]) {
	if (argc < 4 || argc > 5) {
		wrongUsage ();
	}

	D = atoi(argv[1]);
	N = atoi(argv[2]);
	if (argc == 5 && argv[4][0] == 'd') debug = 1;

	if (N <= 4 || D <= 249) wrongUsage ();

	if (argv[3][0] == 'v') RUN_TYPE = 1;
	else if (argv[3][0] == 'u') RUN_TYPE = 0;
	else wrongUsage ();

	srand (time (NULL));

	pista = speedway_create (D);
	team_a = team_create (0, N);
	team_b = team_create (1, N);
	cyclists = malloc(2 * N * sizeof (Cyclist *));
	pthread_mutex_init (&mutex_max_lap, NULL);

	pthread_barrier_init (&first_barrier, NULL, team_a->n + team_b->n);
	pthread_barrier_init (&second_barrier, NULL, team_a->n + team_b->n);
	cur_second_barrier = &second_barrier;

	int count = 0;

	for (int i = 0; i < 2; i++) {
		Team *team = i == 0 ? team_a : team_b;

		for (int j = 0; j < team->n; j++) {
			Cyclist *this = team->cyclists[j];
			this->i = count++;

			if (RUN_TYPE == 0) this->speed = 60;

			cyclists[this->i] = this;

			//cyclist_print (this);

			int result = pthread_create(&(this->tid), NULL, run, this);

			if (result != 0) {
				printf ("Erro criando a thread (%d).\n", j);
				exit (-1);
			}
		}
	}

	for (int i = 0; i < count; i++) {
		pthread_join (cyclists[i]->tid, NULL);
	}

	team_destroy (team_a);
	team_destroy (team_b);
	speedway_destroy (pista);

	pthread_barrier_destroy (&first_barrier);
	pthread_barrier_destroy (&second_barrier);
	pthread_barrier_destroy (&second_barrier_alt);

	pthread_mutex_destroy (&mutex_max_lap);

	free (cyclists);

	return 0;
}
