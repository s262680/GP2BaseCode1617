#include "MyGame.h"


MyGame::MyGame()
{

}

MyGame::~MyGame()
{

}

void MyGame::render()
{
  GameApplication::render();
  //Switch to ModelView
  glMatrixMode( GL_MODELVIEW );
  //Reset using the Identity Matrix
  glLoadIdentity();
  //Translate to -5.0f on z-axis
  glTranslatef(0.0f, 0.0f, -5.0f);
  //Begin drawing triangles
  glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); //Colour of the vertices
    glVertex3f(0.0f, 1.0f, 0.0f); // Top
    glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left
    glVertex3f(1.0f, -1.0f, 0.0f); // Bottom Right
  glEnd();

}
