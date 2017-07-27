#include <math.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include "speedway.h"

#define myMax(a,b) (((a) < (b)) ? (a) : (b))

Speedway *speedway_create(int d) {
	Speedway *speedway = malloc (sizeof (Speedway));
	speedway->slots = malloc (d * sizeof (Slot *));
	speedway->n = d;

	for (int i = 0; i < d; i++) {
		speedway->slots[i] = malloc (sizeof (Slot));
		speedway->slots[i]->cyclists = malloc (2 * sizeof (Cyclist *));

		pthread_mutex_init (&(speedway->slots[i]->mutex), NULL);
	}

	return speedway;
}

void speedway_destroy (Speedway *speedway) {
	for (int i = 0; i < speedway->n; i++) {
		Slot *slot = speedway->slots[i];
		free (slot->cyclists);

		pthread_mutex_destroy (&(slot->mutex));

		free (slot);
	}

  free (speedway->slots);
  free (speedway);
}

int speedway_insertCyclist (Speedway *speedway, Cyclist *cyclist, float position) {
	int n = speedway->n;
	int i = ((int) floor (position)) % n;

	// NOTE: decisão de projeto
	if (i < 0) return 0;

	Slot *slot = speedway->slots[i];

	int result = 0;

	pthread_mutex_lock (&(slot->mutex));
	for (int i = 0; i < 2; i++) {
		if (slot->cyclists[i] == NULL) {
			slot->cyclists[i] = cyclist;
			result = 1;
			break;
		}
	}
	pthread_mutex_unlock (&(slot->mutex));

	return result;
}

void speedway_removeCyclist (Speedway *speedway, Cyclist *cyclist, float position) {
	int n = speedway->n;
	int i = ((int) floor (position)) % n;

	// NOTE: decisão de projeto
	if (i < 0) return;

	Slot *slot = speedway->slots[i];

	pthread_mutex_lock (&(slot->mutex));
	for (int i = 0; i < 2; i++) {
		if (slot->cyclists[i] == cyclist) {
			slot->cyclists[i] = NULL;
			break;
		}
	}
	pthread_mutex_unlock (&(slot->mutex));
}
