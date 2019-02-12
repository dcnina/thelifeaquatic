/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * collision.c
 */

#include "../include/collision.h"


void deleteObject(List element, List *lstObject){
	List firstElement = *lstObject;
	List tmp;

	if(element == *lstObject){
		tmp = *lstObject;
		*lstObject = (*lstObject)->next;
		free(tmp);
		return;
	}

	while((*lstObject)->next != NULL){
		if((*lstObject)->next == element){
			tmp = (*lstObject)->next;
			(*lstObject)->next = (*lstObject)->next->next;
			*lstObject = firstElement;
			free(tmp);
			return;
		}
		*lstObject = (*lstObject)->next;
	}

	if((*lstObject)->next == element){
		tmp = (*lstObject)->next;
		free(tmp);
		(*lstObject)->next = NULL;
		return;
	}
}

int detectCollisionObject(List *lstObject1, List *lstObject2, int type, int bonus){
	List tmpObject2 = *lstObject2;

	if (tmpObject2 != NULL){
		detectCollisionObjectList(lstObject1, lstObject2,type, bonus);
		detectCollisionObject(lstObject1, &(tmpObject2->next),type, bonus);
	}
	return 0;
}

int detectCollisionObjectList(List *lstObject1, List *lstObject2, int type, int bonus){
	List tmpObject1 = *lstObject1;
	List tmpObject2 = *lstObject2;

	if (tmpObject1 != NULL){
		if (tmpObject1->Pmin.posX < tmpObject2->Pmax.posX &&
		tmpObject1->Pmax.posX > tmpObject2->Pmin.posX &&
		tmpObject1->Pmin.posY < tmpObject2->Pmax.posY &&
		tmpObject1->Pmax.posY > tmpObject2->Pmin.posY){
			if (type == 1 && bonus == 0){ /*PLAYER */
				tmpObject2->nbLives--;
				deleteObject(tmpObject1, lstObject1);
				return 1;
			}
			if(type == 1 && bonus == 1){
				tmpObject2->nbLives++;
				deleteObject(tmpObject1, lstObject1);
				return 1;
			}
			tmpObject1->nbLives--;
			deleteObject(tmpObject2, lstObject2);
			if (tmpObject1->nbLives == 0)
				deleteObject(tmpObject1, lstObject1);
			return 1;
		}
		detectCollisionObjectList(&(tmpObject1->next),lstObject2,type, bonus);
	}
	return 0;
}


void detectDeleteElement(List *lst, float xPlayer, unsigned int X_WIDTH){
	List tmpLst = *lst;


	while (tmpLst != NULL){
		if (xPlayer != 0){
			if (tmpLst->Pmax.posX >= (xPlayer+ X_WIDTH))
				deleteObject(tmpLst, lst);

		}
		else{
			if (tmpLst->Pmax.posX <= xPlayer)
				deleteObject(tmpLst, lst);

		}
		tmpLst = tmpLst->next;
	}

}
