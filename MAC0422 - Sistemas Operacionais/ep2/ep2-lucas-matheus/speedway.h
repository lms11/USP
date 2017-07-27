#ifndef __SPEEDWAY_HEADER__
#define __SPEEDWAY_HEADER__

// #include <semaphore.h>
#include <pthread.h>
#include "cyclist.h"

struct slot_struct {
	Cyclist **cyclists;
	pthread_mutex_t mutex;
};
typedef struct slot_struct Slot;

struct speedway_struct {
	Slot **slots;
	int n;
};
typedef struct speedway_struct Speedway;

/*
	Cria uma pista
	@param d Size of speedway
*/
Speedway *speedway_create(int d);

/*
	Destrói a pista
	@param speedway Qual o pista deve ser destruida
*/
void speedway_destroy (Speedway *speedway);

/*
	Adiciona um ciclista
	@param speedway Qual pista estamos trabalhando
	@param cyclist Qual o ciclista deve ser inserido
	@param position Qual posição deve ser inserido

	Retorna 0 se não removeu, não 0 do contrário
*/
int speedway_insertCyclist (Speedway *speedway, Cyclist *cyclist, float position);

/*
	Remove um ciclista
	@param speedway Qual pista estamos trabalhando
	@param cyclist Qual o ciclista deve ser removido
*/
void speedway_removeCyclist (Speedway *speedway, Cyclist *cyclist, float position);

/*
	Imprime a pista
*/
void speedway_print (Speedway *speedway);

#endif
