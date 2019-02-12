/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * menu.c
 */

#include "../include/menu.h"

int detectLevel(unsigned int X_WIDTH, unsigned int Y_HEIGHT, float mouseX, float mouseY){
	mouseX = X_WIDTH-(X_WIDTH * (float)mouseX / 900.);
	mouseY = Y_HEIGHT-(Y_HEIGHT * (float)mouseY / 600.);

	if(mouseX >= X_WIDTH/7. && mouseX <= X_WIDTH*2./7. && mouseY >= Y_HEIGHT-17 && mouseY <= Y_HEIGHT-12)
		return 3;
	if(mouseX >= X_WIDTH*3./7. && mouseX <= X_WIDTH*4./7. && mouseY >= Y_HEIGHT-17 && mouseY <= Y_HEIGHT-12)
		return 2;
	if(mouseX >= X_WIDTH*5./7. && mouseX <= X_WIDTH*6./7. && mouseY >= Y_HEIGHT-17 && mouseY <= Y_HEIGHT-12)
		return 1;
	return 0;
}

void loadLevel(FILE **file, int level, float *levelSpeed){
	if(level == 1){
		if ((*file = fopen("img/level1.ppm","r")) == NULL){
			printf("ERROR: no file ppm\n");
			return;
		}
		*levelSpeed = 1.;
	}
	else if(level == 2){
		if ((*file = fopen("img/level2.ppm","r")) == NULL){
			printf("ERROR: no file ppm\n");
			return;
		}
		*levelSpeed = 1.25;
	}
	else if(level == 3){
		if ((*file = fopen("img/level3.ppm","r")) == NULL){
			printf("ERROR: no file ppm\n");
			return;
		}
		*levelSpeed = 1.5;
	}
}
