#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "cyclist.h"

Cyclist *cyclist_create (int team, float position) {
 Cyclist *cyclist = malloc(sizeof (Cyclist));
 cyclist->position = position;
 cyclist->vector_position = 0; // TODO: conferir isso
 cyclist->team = team;
 cyclist->speed = 30;
 cyclist->time = 0;
 cyclist->broken_at_lap = -1;
 return cyclist;
}

void cyclist_destroy (Cyclist *cyclist) {
  free (cyclist);
}

void cyclist_print (Cyclist *cyclist) {
  printf ("[CICLISTA] Identificador: %d\tPercorreu: %fm\tPosição na pista: ",
    cyclist->i,
    cyclist->position);

  if (cyclist->broken_at_lap == -1) {
    printf ("%d\t", cyclist->vector_position);

  } else {
    printf ("quebrou na volta %d\t", cyclist->broken_at_lap);

  }

  printf ("Tempo: %dms\tTime: %d\tVelocidade atual: %d\n",
    cyclist->time,
    cyclist->team,
    cyclist->speed);
}
