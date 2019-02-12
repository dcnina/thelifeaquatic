/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * world.h
 */
#ifndef DRAW_H
#define DRAW_H

#include "objects.h"

 typedef struct world{
 	List player;
 	List obstacles;
 	List enemies;
	List missiles;
	List projectiles;
	List bonus;
 }world, *World;

/* Description : allocate and initialize a world
 * Parameters : *world
 * Return : 0 if problem in the allocation, 1 if ok
 */
int createWorld(World *world);

/* Description : initialize a world
 * Parameters : *world, *ppmFile, *xFinishLine (finish line position), levelSpeed (float)
 */
void initializeWorld(World *world, FILE *ppmFile, float *xFinishLine,  float levelSpeed);

/* Description : free a world
 * Parameters : *world
 */
void freeWorld(World *world);

#endif
