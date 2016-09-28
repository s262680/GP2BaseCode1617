#include "MyGame.h"

struct Vertex{
	float x,y,z;
  float r,g,b,a;
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
  	{-0.5f, -0.5f, 0.0f,    1.0f,0.0f,0.0f,1.0f},
    {0.5f, -0.5f, 0.0f,     0.0f,1.0f,0.0f,1.0f},
  	{0.0f,  0.5f, 0.0f,     0.0f,0.0f,1.0f,1.0f}
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
  glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);

  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void**)(3 * sizeof(float)));

  glDrawArrays(GL_TRIANGLES, 0, 3);
}
