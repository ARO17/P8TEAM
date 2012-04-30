/*
 * triangle_opengl.cpp
 * 
 * g++ -Wall triangle_opengl.cpp -o triangle_opengl -lGL -lGLU -lSDL
 *
 */

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define LARGEUR_ECRAN 640
#define HAUTEUR_ECRAN 480

/*
    Dessine le repère actuel pour faciliter
    la compréhension des transformations.
    Utiliser « echelle » pour avoir un repère bien orienté et positionné
    mais avec une échelle différente.
*/
void dessinerRepere(unsigned int echelle = 1)
{
    glPushMatrix();
    glScalef(echelle,echelle,echelle);
    glBegin(GL_LINES);
    glColor3ub(0,0,255);
    glVertex2i(0,0);
    glVertex2i(1,0);
    glColor3ub(0,255,0);
    glVertex2i(0,0);
    glVertex2i(0,1);
    glEnd();
    glPopMatrix();
}

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("La grue !",NULL);
  SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_OPENGL);
  SDL_EnableKeyRepeat(10,10);

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluOrtho2D(0,LARGEUR_ECRAN,0,HAUTEUR_ECRAN);
  

  bool continuer = true;
  SDL_Event event;
  SDLMod mod = KMOD_NONE;

  while (continuer)
    {
      SDL_WaitEvent(&event);
      mod = SDL_GetModState();
      switch(event.type)
        {
	case SDL_QUIT:
	  continuer = false;
	  break;
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
            {
	    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
	      continuer = false;
	      break;
	    case SDLK_UP:
	      glRotated(45,0,0,1);
	      break;
	    case SDLK_DOWN:
	      glRotated(45,0,0,1);
	      break;
	    case SDLK_LEFT:
	      if (mod & KMOD_SHIFT)
		glRotated(45,0,0,1);
	      break;
	    case SDLK_RIGHT:
	      glRotated(-45,0,0,1);
	      break;
	    case SDLK_h:
	      dessinerRepere(50);
	      break;
	    default:
	      break;
            }
	  break;
	default:
	  break;
        }

      glClear(GL_COLOR_BUFFER_BIT);
      
      glBegin(GL_QUADS);
      glColor3ub(255, 0, 0);    glVertex2d(20, 20);
      glColor3ub(0, 255, 0);    glVertex2d(20, 50);
      glColor3ub(0, 0, 255);    glVertex2d(80, 60);
      glColor3ub(0, 0, 255);    glVertex2d(80, 30);
      glEnd();
      
      glFlush();
      SDL_GL_SwapBuffers();
    }

  SDL_Quit();

  return 0;
}
