/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * objects.c
 */


#include "../include/objects.h"

Coord createCoord(float x, float y){
	Coord coordinate;
	coordinate.posX = x;
	coordinate.posY = y;

	return coordinate;
}

List allocObject(Coord Pmin, float speedX, float speedY, float height, float width, int nbLives){
	List tmp;

	if (NULL == (tmp = malloc(sizeof(Cell))))
		return NULL;

	tmp->Pmin.posX = Pmin.posX;
	tmp->Pmin.posY = Pmin.posY;
	tmp->Pmax.posX = Pmin.posX + width;
	tmp->Pmax.posY = Pmin.posY + height;
	tmp->speedX = speedX;
	tmp->speedY = speedY;
	tmp->height = height;
	tmp->width = width;
	tmp->nbLives = nbLives;

	tmp->next = NULL;

	return tmp;
}

int addObjectToList(List *lst, List cell){
	if((*lst) == NULL)
		(*lst) = cell;
	else{
		cell->next = (*lst);
		(*lst) = cell;
	}
	return 1;
}

void addObjectToListEnd(List *lst, List cell){
	List tmp = *lst;

	if((*lst) == NULL){
		(*lst) = cell;
		return;
	}

	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = cell;
}

void launchProjectiles(List *lstProjectiles, List *lstEnemies, List player, unsigned int X_WIDTH){
	List tmp = *lstEnemies;

	while (tmp != NULL){
		if(tmp->Pmin.posX <= (X_WIDTH + player->Pmax.posX) && tmp->Pmin.posX >= player->Pmax.posX)
			addObjectToList(&(*lstProjectiles), allocObject(createCoord(tmp->Pmin.posX, tmp->Pmin.posY),0.5, 0., 1 , 1, 1));
		tmp = tmp->next;
	}
}

void printList(List lst){
	List tmp = lst;

	while (tmp != NULL){
		printf("Coordinates pmin : (%f, %f), Coordonates pmax : (%f, %f)\n", tmp->Pmin.posX, tmp->Pmin.posY, tmp->Pmax.posX, tmp->Pmax.posY);
		tmp = tmp->next;
	}
	printf("end list\n");
}

int numberElementList(List lst){
	int nb = 0;
	List tmp = lst;

	while (tmp != NULL){
		nb ++;
		tmp = tmp->next;
	}
	return nb;
}

void freeList(List *lst){
	List tmp;

	while (*lst != NULL){
		tmp = (*lst)->next;
		free(*lst);
		(*lst) = tmp;
	}
}
