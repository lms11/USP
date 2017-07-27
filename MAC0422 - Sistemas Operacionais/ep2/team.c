#include <stdio.h>
#include <stdlib.h>
#include "team.h"
#include "cyclist.h"

Team *team_create(int id, int n) {
	Team *team = malloc (sizeof (Team));
  team->id = id;
	team->n = n;
	team->cyclists = malloc(n * sizeof (Cyclist *));
	for (int i = 0; i < n; i++) {
		team->cyclists[i] = cyclist_create (id, 0);
	}
	return team;
}

void team_destroy (Team *team) {
  for (int i = 0; i < team->n; i++) {
    cyclist_destroy (team->cyclists[i]);
  }

	free (team->cyclists);
  free (team);
}

void team_print (Team *team, int n) {
  printf("[TIME] Identificador: %d\tNúmero de ciclistas (ainda competindo): %d\tCiclistas:\n",
    team->id,
    team->n);

  for (int i = 0; i < n; i++) {
    printf("  ");
    cyclist_print (team->cyclists[i]);
  }
}
