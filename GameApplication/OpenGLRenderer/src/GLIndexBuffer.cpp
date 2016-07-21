#include "GLIndexBuffer.h"
#include <SDL_opengl.h>

GLIndexBuffer::GLIndexBuffer()
{
  m_IBO=0;
  m_numIndices=0;
}

GLIndexBuffer::~GLIndexBuffer()
{
  destroy();
}

bool GLIndexBuffer::init(int *pIndices, int numIndices)
{
  glGenBuffers(1, &m_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(int),pIndices, GL_STATIC_DRAW);
  m_numIndices=numIndices;
  return true;
}

void GLIndexBuffer::destroy()
{
    glDeleteBuffers(1,&m_IBO);
}

void GLIndexBuffer::bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
}
