#ifndef __CYCLIST_HEADER__
#define __CYCLIST_HEADER__

struct struct_cyclist {
	pthread_t tid;

	float position;
	int vector_position;
	int team;            // 0 ou 1
	int speed;           // 30 ou 60
  int i;
	int time;
	int broken_at_lap;
};
typedef struct struct_cyclist Cyclist;

/*
	Cria ciclista
	@param team Time do ciclista
*/
Cyclist *cyclist_create (int team, float position);

/*
	Destrói um ciclista
	@param cyclist Qual o ciclista deve ser destruido
*/
void cyclist_destroy (Cyclist *cyclist);

/*
	Imprimi um ciclista (debug)
	@param cyclist Qual o ciclista deve ser impresso
*/
void cyclist_print (Cyclist *cyclist);

#endif
