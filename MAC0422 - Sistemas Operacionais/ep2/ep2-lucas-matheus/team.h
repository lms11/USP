#ifndef __TEAM_HEADER__
#define __TEAM_HEADER__

#include "cyclist.h"

struct team_struct {
	Cyclist **cyclists;
	int n; 							// número de ciclistas
  int id;             // 0 ou 1
};
typedef struct team_struct Team;

/*
	Cria equipe
	@param n Número de ciclistas
	@param t Qual equipe (0 ou 1)
*/
Team *team_create(int id, int n);

/*
	Destrói um time
	@param team Qual o time deve ser destruido
*/
void team_destroy (Team *team);

/*
	Imprimi um time (debug)
	@param team Qual o time deve ser impresso
	@param n Imprime os N primeiros ciclistas
*/
void team_print (Team *team, int n);

#endif
