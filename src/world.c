/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * world.c
 */


#include "../include/world.h"

int createWorld(World *world){
	*world = (World)malloc(sizeof(List)*6);
	if (*world == NULL)
		return 0;
	(*world)->obstacles = NULL;
	(*world)->enemies = NULL;
	(*world)->player = NULL;
	(*world)->missiles = NULL;
	(*world)->projectiles = NULL;
	(*world)->bonus = NULL;
	return 1;
}


void initializeWorld(World *world, FILE *ppmFile, float *xFinishLine,  float levelSpeed){
	int nbLines = 0;
	int r, g, b, err;
	char c;
	int x = 0, y = 19;

	/*to start after the 4 informations lines*/
	while (nbLines != 4){
		c = fgetc(ppmFile);
		if(c == '\n')
			nbLines ++;
	}

	/*read the file*/
	while (!feof(ppmFile)){

		if (x == 275){
			y--;
			x = 0;
		}
		//scan the colors
		if ((err = fscanf(ppmFile, "%d\n%d\n%d\n", &r, &g, &b)) != 3){
			printf("ERROR: fscanf ppm\n");
			return;
		}
		if (r != 255 || g != 255 || b != 255){
			if (r == 215 && g == 158 && b == 51) /* PLAYER*/
				addObjectToList(&((*world)->player), allocObject(createCoord(x, y), 0.05*levelSpeed, 0, 2, 2.5, 4));

			else if (r == 0 && g == 0 && b == 255) /* ENEMIES */
				addObjectToList(&((*world)->enemies), allocObject(createCoord(x, y), 0.1*levelSpeed, 0.2,2, 4, 1));

			else if (r == 255 && g == 0 && b == 0) /*OBSTACLES*/
				addObjectToList(&((*world)->obstacles), allocObject(createCoord(x, y), 0.05*levelSpeed, 0, 2, 2, 2));

			else if (r == 0 && g == 255 && b ==0)
				*xFinishLine = x;
			
			else if(r == 0 && g == 0 && b == 0)
				addObjectToList(&((*world)->bonus), allocObject(createCoord(x, y), 0.05*levelSpeed, 0, 1.3, 1.5, 1));
				
		}
		x++;
	}
}

void freeWorld(World *world){
	freeList(&((*world)->player));
	freeList(&((*world)->obstacles));
	freeList(&((*world)->enemies));
	freeList(&((*world)->missiles));
	freeList(&((*world)->projectiles));
	freeList(&((*world)->bonus));
	*world = NULL;
}
