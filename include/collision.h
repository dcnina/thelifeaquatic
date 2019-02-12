/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * collision.h
 */

#include "../include/world.h"

/*Description : delete object from list
 *Parameters : lstElement (object to delete), *lstObject (list)
 *Return : -
 */
void deleteObject(List lstElement, List *lstObject);

/*Description : detect a collision between 2 objects
 *Parameters : *lstObject1 (list 1), *lstObject2 (list 2), type (int), bonus (int)
 *Return : 1 if collision, 0 else
 */
int detectCollisionObject(List *lstObject1, List *lstObject2, int type, int bonus);

/*Description : function annexe to detectCollisionObject
 *Parameters : *lstObject1 (list 1), *lstObject2 (list 2), type (int), bonus (int)
 *Return : 1 if collision, 0 else
 */
int detectCollisionObjectList(List *lstObject1, List *lstObject2, int type, int bonus);

/*Description : detect and delete a object out of the screen
 *Parameters : *lst (List), xPlayer (float),  X_WIDTH (unsigned int)
 *Return : 1 if collision, 0 else
 */
void detectDeleteElement(List *lst, float xPlayer, unsigned int X_WIDTH);
