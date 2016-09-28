#include "MyGame.h"

struct Vertex{
	float x,y,z;
 };

MyGame::MyGame()
{

}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{
  glGenBuffers(1, &m_VBO);
  Vertex verts[]={
    {-0.5f, -0.5f, 0.0f},
    {0.5f, -0.5f, 0.0f},
    {0.0f,  0.5f, 0.0f}
  };

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

  glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex), verts, GL_STATIC_DRAW);
}

void MyGame::destroyScene()
{
  glDeleteBuffers(1,&m_VBO);
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
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
