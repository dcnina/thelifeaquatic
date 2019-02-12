/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * draw.c
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "../include/draw.h"

GLuint createTexture(char *name){

	// Loading and processing of the texture
	SDL_Surface *object;
	object = IMG_Load(name);

	if(object == NULL)
		printf("error with the image %s\n", name);

	//Creation of texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	//Attach texture to bind point

	glBindTexture(GL_TEXTURE_2D, textureID);

	//Datas loading on the graphic card
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		object->w,
		object->h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		object->pixels
	);

	//Remove texture of its bind point
	glBindTexture(GL_TEXTURE_2D, 0);

	// Free CPU datas
	SDL_FreeSurface(object);

	return textureID;
}

GLuint createTextureRepeat(char *name){

	// Loading and processing of the texture
	SDL_Surface *object;
	object = IMG_Load(name);

	if(object == NULL)
		printf("error with the image %s\n", name);

	//Creation of texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	//Attach texture to bind point

	glBindTexture(GL_TEXTURE_2D, textureID);

	//Datas loading on the graphic card
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		object->w,
		object->h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		object->pixels
	);

	//Remove texture of its bind point
	glBindTexture(GL_TEXTURE_2D, 0);

	// Free CPU datas
	SDL_FreeSurface(object);

	return textureID;
}

void drawLives(GLuint textureID, int nbLives){
	int i;
	
	glBindTexture(GL_TEXTURE_2D, textureID); //binding the texture to use it
	
	for(i=1; i<=nbLives; i++){
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);
				glVertex2f(X_WIDTH-(i*2), Y_HEIGHT-1);
				glTexCoord2f(1,0);
				glVertex2f(X_WIDTH-(i*2+1.5), Y_HEIGHT-1);
				glTexCoord2f(1,1);
				glVertex2f(X_WIDTH-(i*2+1.5), Y_HEIGHT-2.3);
				glTexCoord2f(0,1);
				glVertex2f(X_WIDTH-(i*2), Y_HEIGHT-2.3);
			glEnd();
		glPopMatrix();
	}
}

void drawFinishLine(GLuint textureEnd, float *xFinishLine){
	glBindTexture(GL_TEXTURE_2D, textureEnd); //binding the texture to use it
	glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);
				glVertex2f(*xFinishLine, Y_HEIGHT);
				glTexCoord2f(1,0);
				glVertex2f(*xFinishLine + 2, Y_HEIGHT);
				glTexCoord2f(1,1);
				glVertex2f(*xFinishLine + 2, 0);
				glTexCoord2f(0,1);
				glVertex2f(*xFinishLine, 0);
			glEnd();
		glPopMatrix();
	
}

void drawBackground(GLuint textureID, float *posBg1, float levelSpeed){

	glBindTexture(GL_TEXTURE_2D, textureID); //binding the texture to use it
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0 + *posBg1, 0);
			glVertex2f(0, Y_HEIGHT);
			glTexCoord2f(1 + *posBg1,0);
			glVertex2f(X_WIDTH, Y_HEIGHT);
			glTexCoord2f(1 + *posBg1,1);
			glVertex2f(X_WIDTH, 0);
			glTexCoord2f(0 + *posBg1,1);
			glVertex2f(0, 0);
		glEnd();

		*posBg1 += 0.0025*levelSpeed;
	glPopMatrix();

}

void drawElements(GLuint textureID, List lst){
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, textureID); //binding the texture to use it

	List tmp = lst;
	float elementPminX;
	float elementPminY;
	float elementWidth;
	float elementHeight;

	while (tmp != NULL){
		elementPminX = tmp->Pmin.posX;
		elementPminY = tmp->Pmin.posY;
		elementHeight = tmp->Pmin.posY + tmp->height;
		elementWidth = tmp->Pmin.posX + tmp->width;

			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);
				glVertex2f(elementWidth, elementHeight);
				glTexCoord2f(1,0);
				glVertex2f(elementPminX, elementHeight);
				glTexCoord2f(1,1);
				glVertex2f(elementPminX, elementPminY);
				glTexCoord2f(0,1);
				glVertex2f(elementWidth, elementPminY);
			glEnd();

		tmp = tmp->next;
	}
}

void drawMenu(GLuint textureID[]){
	//title
	glBindTexture(GL_TEXTURE_2D, textureID[3]); //binding the texture to use it
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(X_WIDTH/5, Y_HEIGHT-2);
			glTexCoord2f(1,0);
			glVertex2f(X_WIDTH*4/5, Y_HEIGHT-2);
			glTexCoord2f(1,1);
			glVertex2f(X_WIDTH*4/5, Y_HEIGHT-10);
			glTexCoord2f(0,1);
			glVertex2f(X_WIDTH/5, Y_HEIGHT-10);
		glEnd();
	glPopMatrix();
	
	//level1
	glBindTexture(GL_TEXTURE_2D, textureID[0]); //binding the texture to use it
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(X_WIDTH/7., Y_HEIGHT-12);
			glTexCoord2f(1,0);
			glVertex2f(X_WIDTH*2./7., Y_HEIGHT-12);
			glTexCoord2f(1,1);
			glVertex2f(X_WIDTH*2./7., Y_HEIGHT-17);
			glTexCoord2f(0,1);
			glVertex2f(X_WIDTH/7., Y_HEIGHT-17);
		glEnd();
	glPopMatrix();
	
	
	//level2
	glBindTexture(GL_TEXTURE_2D, textureID[1]); //binding the texture to use it
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(X_WIDTH*3./7., Y_HEIGHT-12);
			glTexCoord2f(1,0);
			glVertex2f(X_WIDTH*4./7., Y_HEIGHT-12);
			glTexCoord2f(1,1);
			glVertex2f(X_WIDTH*4./7., Y_HEIGHT-17);
			glTexCoord2f(0,1);
			glVertex2f(X_WIDTH*3./7., Y_HEIGHT-17);
		glEnd();
	glPopMatrix();
	
	
	
	//level3
	glBindTexture(GL_TEXTURE_2D, textureID[2]); //binding the texture to use it
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(X_WIDTH*5./7., Y_HEIGHT-12);
			glTexCoord2f(1,0);
			glVertex2f(X_WIDTH*6./7., Y_HEIGHT-12);
			glTexCoord2f(1,1);
			glVertex2f(X_WIDTH*6./7., Y_HEIGHT-17);
			glTexCoord2f(0,1);
			glVertex2f(X_WIDTH*5./7., Y_HEIGHT-17);
		glEnd();
	glPopMatrix();
}

void drawEndMessage(GLuint textureID){
	
	glBindTexture(GL_TEXTURE_2D, textureID); //binding the texture to use it
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(X_WIDTH/6, Y_HEIGHT-7);
			glTexCoord2f(1,0);
			glVertex2f(X_WIDTH*5/6, Y_HEIGHT-7);
			glTexCoord2f(1,1);
			glVertex2f(X_WIDTH*5/6, Y_HEIGHT-13);
			glTexCoord2f(0,1);
			glVertex2f(X_WIDTH/6, Y_HEIGHT-13);
		glEnd();
	glPopMatrix();	
}

void drawWorld(World world, GLuint textureID[], GLuint textureEnd, float *xFinishLine){
		
		drawElements(textureID[0], world->player);
		drawElements(textureID[1], world->enemies);
		drawElements(textureID[2], world->obstacles);
		drawElements(textureID[3], world->missiles);
		drawElements(textureID[4], world->projectiles);	
		drawElements(textureID[5], world->bonus);	
		drawFinishLine(textureEnd, xFinishLine);
}
