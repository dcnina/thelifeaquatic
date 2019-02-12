/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * menu.h
 */

#include <stdlib.h>
#include <stdio.h>

/*Description : detect level selected
 *Parameters : X_WIDTH, Y_HEIGHT, mouseX, mouseY (position of the click)
 *Return : 1 if level 1 selected, 2 if leve 2, 3 if level 3, 0 else
 */
int detectLevel(unsigned int X_WIDTH, unsigned int Y_HEIGHT, float mouseX, float mouseY);

/*Description : load a level
 *Parameters : **file (level file), level, *levelSpeed (float)
 */
void loadLevel(FILE **file, int level,  float *levelSpeed);