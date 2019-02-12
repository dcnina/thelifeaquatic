/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * main.c
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <stdlib.h>

#include <math.h>
#include <time.h>

#include "../include/move.h"
#include "../include/draw.h"
#include "../include/collision.h"
#include "../include/menu.h"

#define NB_SEG 100

/* Window's size */
static unsigned int WINDOW_WIDTH = 900;
static unsigned int WINDOW_HEIGHT = 600;

/* Bit per pixel of the window */
static const unsigned int BIT_PER_PIXEL = 32;


static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0., X_WIDTH, 0., Y_HEIGHT);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL);
}

int main(int argc, char** argv) {
	int menu = 0;
	float levelSpeed = 0;
	float posBackground1 = 0.0;
	int loop = 1;
    float playerMode = 0;
	float xPlayer = 0.0;
	float yPlayer = 0.0;
    float missileMode = 0;
	float xFinishLine;
	int timerEnd = 0;
	int lastTime =0;
	int currentTime;
	FILE *file = NULL;
	World world = NULL;
	

	/* Initialization of SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        fprintf(stderr, "Impossible to initialize SDL. End of programme.\n");
        return EXIT_FAILURE;
    }

    /* Creation and opening window */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER)) {
        fprintf(stderr, "Impossible to open the window. End of programme.\n");
        return EXIT_FAILURE;
    }

    /* Window's title */
    SDL_WM_SetCaption("THE LIFE AQUATIC", NULL);
    resizeViewport();
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapBuffers();

    //Creation of Background texture
    GLuint textureIDBackground = createTextureRepeat("img/background.png");

	//Creation of menu texture
	GLuint textureIDMenu[4];
	textureIDMenu[0] = createTexture("img/buoy1.png");
    textureIDMenu[1] = createTexture("img/buoy2.png");
	textureIDMenu[2] = createTexture("img/buoy3.png");
	textureIDMenu[3] = createTexture("img/title.png");

	//Creation of elements textures
	GLuint textureIDElements[6];
    textureIDElements[0] = createTexture("img/player.png");
    textureIDElements[1] = createTexture("img/shark.png");
	textureIDElements[2] = createTexture("img/obstacles.png");
    textureIDElements[3] = createTexture("img/shoes.png");
    textureIDElements[4] = createTexture("img/urchin.png");
    textureIDElements[5] = createTexture("img/cap.png");

	GLuint textureIDLives = createTexture("img/cap.png");
	GLuint textureEnd = createTexture("img/finishline.png");
	GLuint textureGameOver = createTexture("img/gameover.png");
	GLuint textureYouWin = createTexture("img/youwin.png");

	//Sound initialization
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
		printf("%s\n", Mix_GetError());
	Mix_Music *music; //creation of musique
	Mix_Chunk *bloop;
	Mix_Chunk *boom;

	music = Mix_LoadMUS("sound/music.mp3");
	bloop = Mix_LoadWAV("sound/bloop.wav");
	boom = Mix_LoadWAV("sound/boom.wav");
	if( boom ==NULL)
		return 0;
	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME);
	Mix_VolumeChunk(boom, MIX_MAX_VOLUME*2);

	glEnable(GL_BLEND);
	glClearColor(0, 0, 0, 0);
	/* Loop */
    while(loop) {
        /* get time at the beginning of loop */
        Uint32 startTime = SDL_GetTicks();
        glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D); //precise texturing fonctionnality activation

		/* Menu */
		if (menu == 0){
			timerEnd = 0;
			//Draw Brackground
			drawBackground(textureIDBackground, &posBackground1, levelSpeed);
			drawMenu(textureIDMenu);
			SDL_GL_SwapBuffers();
			/* Events loop */
			int click;
	        SDL_Event e;
	        while (SDL_WaitEvent(&e) && menu != 1) {
	            /* user closes the window : */
	            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == 113)) {
	                loop = 0;
					menu = 1;
	            }
				/* events : */
				switch (e.type) {
					case SDL_MOUSEBUTTONDOWN:
						click = detectLevel(X_WIDTH, Y_HEIGHT, e.button.x, e.button.y);
						if (click != 0){
							menu = 1;
							createWorld(&world);
							loadLevel(&file, click, &levelSpeed);
							initializeWorld(&world, file, &xFinishLine, levelSpeed);
							fclose(file);
						}
						break;
					default:
						break;
				}
	        }
			SDL_GL_SwapBuffers();
		}
		if (loop != 0){
			/* Delete and delete elements out of the screen */
			detectDeleteElement(&(world->missiles), world->player->Pmin.posX, X_WIDTH);
			detectDeleteElement(&(world->obstacles), 0, X_WIDTH);
			detectDeleteElement(&(world->enemies), 0, X_WIDTH);
			detectDeleteElement(&(world->projectiles), 0, X_WIDTH);


			/* Elements move */
			movePlayerY(world->player, playerMode, Y_HEIGHT);
			movePlayerX(world->player);
			moveObjects(world->enemies, Y_HEIGHT);
			moveObjects(world->obstacles, Y_HEIGHT);
			moveObjects(world->missiles, Y_HEIGHT);
			moveObjects(world->bonus, Y_HEIGHT);

			currentTime = SDL_GetTicks();
			if (currentTime > lastTime + 3000){
				launchProjectiles(&(world->projectiles), &(world->enemies), world->player, X_WIDTH);
				lastTime = currentTime;
			}

			//Test collision
			if (detectCollisionObject(&(world->enemies), &(world->missiles), 0, 0) == 1)
				Mix_PlayChannel(1,boom, 0);
			if (detectCollisionObject(&(world->obstacles), &(world->missiles), 0, 0) == 1)
				Mix_PlayChannel(1,boom, 0);
			if (detectCollisionObject(&(world->projectiles), &(world->missiles), 0, 0) == 1)
				Mix_PlayChannel(1,boom, 0);
			if (detectCollisionObject(&(world->obstacles), &(world->player), 1, 0) == 1)
				Mix_PlayChannel(1,boom, 0);
			if (detectCollisionObject(&(world->enemies), &(world->player), 1, 0) == 1)
				Mix_PlayChannel(1,boom, 0);
			if (detectCollisionObject(&(world->bonus), &(world->player), 1, 1) == 1)
				world->player->nbLives++;

			if (world->projectiles != NULL)
				moveObjects(world->projectiles, Y_HEIGHT);
			
			if (detectCollisionObject(&(world->projectiles), &(world->player), 1, 0) == 1)
				Mix_PlayChannel(1,boom, 0);

			if (world->player->nbLives == 0){
				while (timerEnd != 80){
					drawBackground(textureIDBackground, &posBackground1, levelSpeed);
					drawEndMessage(textureGameOver);
					SDL_GL_SwapBuffers();
					timerEnd ++;
				}
				playerMode = 0;
				freeWorld(&world);
				menu = 0;
			}

			//Test end level
			if (menu != 0){
				if (world->player->Pmax.posX >= xFinishLine){
					while (timerEnd != 50){
						drawBackground(textureIDBackground, &posBackground1, levelSpeed);
						drawEndMessage(textureYouWin);
						SDL_GL_SwapBuffers();
						timerEnd ++;
					}
					freeWorld(&world);
					menu = 0;
				}
				if (menu != 0)
					xFinishLine -= world->player->speedX;
			}


			if (menu != 0){
				if (missileMode == 1){
					addObjectToListEnd(&(world->missiles), allocObject(createCoord(xPlayer+1, yPlayer), -0.5, 0, 0.7, 1.8, 1));
					Mix_PlayChannel(-1,bloop, 0);
					missileMode = 0;
				}
				//Draw Brackground
				drawBackground(textureIDBackground, &posBackground1, levelSpeed);
				//Draw World
				glPushMatrix();
					glTranslatef(2-world->player->Pmin.posX, 0, 0);
					drawWorld(world, textureIDElements, textureEnd, &xFinishLine);
				glPopMatrix();
				//Draw lives
				drawLives(textureIDLives, world->player->nbLives);

				glDisable(GL_TEXTURE_2D); //Deactivation of texturing foncionnality
				glBindTexture(GL_TEXTURE_2D, 0);//Debind of the texture

				/* DRAWINGS */
				SDL_GL_SwapBuffers();

				/* Events loop */
				SDL_Event e;
				while (SDL_PollEvent(&e)) {

					/* user closes the window : */
					if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == 113)) {
						loop = 0;
					}
					missileMode = 0;
					/* events : */
					switch (e.type) {
						case SDL_VIDEORESIZE:
							WINDOW_HEIGHT = e.resize.h;
							WINDOW_WIDTH = e.resize.w;
							resizeViewport();
							break;
						case SDL_KEYDOWN :

							switch(e.key.keysym.sym){
								case SDLK_SPACE :
									xPlayer = world->player->Pmax.posX;
									yPlayer = world->player->Pmin.posY;
									missileMode = 1;
									break;

								case SDLK_UP :
									playerMode = 1;
									break;

								case SDLK_DOWN :
									playerMode = -1;
									break;

								default :
									missileMode = 0;
									break;

							}
							break;

						case SDL_KEYUP :
							if(e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP)
						   		playerMode = 0;
							missileMode = 0;
							break;
						default:
							break;
					}
				}
				/* Calculation of time past */
				Uint32 elapsedTime = SDL_GetTicks() - startTime;

				/* if to little time past, programm break */
				if(elapsedTime < FRAMERATE_MILLISECONDS) {
					SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
				}
			}
		}

    }

	// Free GPU datas
    glDeleteTextures(1, &textureIDBackground);

	glDeleteTextures(1, &textureEnd);
	glDeleteTextures(1, &textureGameOver);
	glDeleteTextures(1, &textureYouWin);
	glDeleteTextures(1, &textureIDLives);
	glDeleteTextures(6, textureIDElements);

	glDeleteTextures(4, textureIDMenu);

	//Free music data
	Mix_FreeMusic(music);
	Mix_FreeChunk(bloop);
	Mix_FreeChunk(boom);
	Mix_CloseAudio();

	// Free world
	if (world != NULL)
		freeWorld(&world);

    /* Free SDL resources */
    SDL_Quit();

    return EXIT_SUCCESS;
}
