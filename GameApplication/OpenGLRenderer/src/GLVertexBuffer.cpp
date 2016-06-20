#include "GLVertexBuffer.h"


GLVertexBuffer::GLVertexBuffer()
{
  m_VBO=0;
  m_numVerts=0;
}

GLVertexBuffer::~GLVertexBuffer()
{
  destroy();
}

bool GLVertexBuffer::init(Vertex *pVertex,int numVerts)
{
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(Vertex),pVertex, GL_STATIC_DRAW);

  m_numVerts=numVerts;

  return true;
}

void GLVertexBuffer::destroy()
{
  glDeleteBuffers(1,&m_VBO);
}

void GLVertexBuffer::bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}
