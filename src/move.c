/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * move.c
 */

#include "../include/move.h"


void movePlayerX(List player){
	float moveX = player->Pmin.posX + player->speedX;

	player->Pmin.posX = moveX;
	player->Pmax.posX = moveX + 1.;
}

void movePlayerY(List player, float moveY, unsigned int windowHeight){
	if(player->Pmax.posY + (moveY) <= (windowHeight)  && player->Pmin.posY + (moveY) >= 0){
		player->Pmin.posY += moveY/2;
		player->Pmax.posY += moveY/2;
	}
}

void moveObjects(List objects, unsigned int windowHeight){
	List tmp = objects;

	while(tmp != NULL){
		tmp->Pmin.posX -= objects->speedX;
		tmp->Pmax.posX -= objects->speedX;
		if(tmp->Pmin.posY + tmp->speedY <= 0 || tmp->Pmax.posY + tmp->speedY >= windowHeight)
			tmp->speedY = -tmp->speedY;
		tmp->Pmin.posY += tmp->speedY;
		tmp->Pmax.posY += tmp->speedY;

		tmp = tmp->next;
	}
}
