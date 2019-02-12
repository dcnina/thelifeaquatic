/* COMBE Audrey, DE CASTRO Nina TD2
 * Projet de synthèse d'images
 * draw.h
 */

#include <stdlib.h>
#include <stdio.h>

#include "../include/world.h"

/*orthonormal coordinate system*/
static unsigned int X_WIDTH = 30.;
static unsigned int Y_HEIGHT = 20.;


/*Description : create a texture
 *Parameters : *name (texture file)
 *Return : texture
 */
GLuint createTexture(char *name);

/*Description : create a texture with a repeat parameter
 *Parameters : *name (texture file)
 *Return : texture
 */
GLuint createTextureRepeat(char *name);

/*Description : draw player's lives number
 *Parameters : textureID, number of lives
 */
void drawLives(GLuint textureID, int nbLives);

/*Description : draw level finish line texture
 *Parameters : textureEnd, *xFinishLine (position of finish line)
 */
void drawFinishLine(GLuint textureEnd, float *xFinishLine);

/*Description : draw background texture
 *Parameters : textureID, *posBg1 (moving position of background), levelSpeed (float)
 */
void drawBackground(GLuint textureID, float *posBg1, float levelSpeed);

/*Description : draw element's list
 *Parameters : textureID, lst (list of elements)
 */
void drawElements(GLuint textureID, List lst);

/*Description : draw menu (title, levels to select)
 *Parameters : textureID[]
 */
void drawMenu(GLuint textureID[]);

/*Description : draw end message texture
 *Parameters : textureID
 */
void drawEndMessage(GLuint textureID);

/*Description : draw the world (elements and finish line)
 *Parameters : world, textureID[] (elements), textureEnd (finish line), *xFinishLine (position of finish line)
 */
void drawWorld(World world, GLuint textureID[], GLuint textureEnd, float *xFinishLine);

