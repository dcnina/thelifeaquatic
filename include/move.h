/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * move.h
 */

#ifndef MOVE_H
#define MOVE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../include/world.h"


/*Description : move the player's position in X
 *Parameters : player
 */
void movePlayerX(List player);

/*Description : move the player's position in Y
 *Parameters : player, moveY (value of move), windowHeight
 */
void movePlayerY(List player, float moveY, unsigned int windowHeight);

/*Description : move elements' list position
 *Parameters : objects (list), windowHeight
 */
void moveObjects(List objects, unsigned int windowHeight);

#endif