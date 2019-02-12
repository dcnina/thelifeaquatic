/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * objects.h
 */

#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct coordinates{
	float posX;
	float posY;
} Coord;

typedef struct cell{
	Coord Pmin;
	Coord Pmax;
	float speedX;
	float speedY;
	float height;
	float width;
	int nbLives;
	struct cell *next;
}Cell, *List;

/* Description : create and initialize an object Coord
 * Parameters : float x and float y
 * Return : object Coord
 */
Coord createCoord(float x, float y);

/* Description : allocate and initialize of an object (type list)
 * Parameters : Pmin (coord), speedX, speedY, height, width, nbLives
 * Return : list
 */
List allocObject(Coord Pmin, float speedX, float speedY, float height, float width, int nbLives);

/* Description : add a cellule at the beginning of a list
 * Parameters : *lst (list), cell
 * Return : 1 if ok
 */
int addObjectToList(List *lst, List cell);

/* Description : add a cellule at the end of a list
 * Parameters : *lst (list), cell
 */
void addObjectToListEnd(List *lst, List cell);

/*Description : launch projectiles from enemies position (add object to list projectiles)
 *Parameters : *lstProjectiles, *lstEnemies, X_WIDTH
*/
void launchProjectiles(List *lstProjectiles, List *lstEnemies, List player, unsigned int X_WIDTH);

/* Description : printf all the elements of a list
 * Parameters : lst
 */
void printList(List lst);

/*Description : count number of element in a list
 *Parameters : lst
 *Return : number of elements
 */
int numberElementList(List lst);

/* Description : free a list
 * Parameters : *lst
 */
void freeList(List *lst);

#endif
