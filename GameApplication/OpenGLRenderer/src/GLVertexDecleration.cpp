#include "GLVertexDecleration.h"

GLVertexDecleration::GLVertexDecleration()
{
  m_VAO=0;
}

GLVertexDecleration::~GLVertexDecleration()
{
  destroy();
}

void GLVertexDecleration::setVeretxFormat(VertexFormat *pFormat)
{
  glGenVertexArrays(1,&m_VAO);
  glBindVertexArray(m_VAO);
  int size=(sizeof(pFormat)/sizeof(VertexFormat));
  for (int i=0;i<size;i++)
  {
    //Setup GL Pointer
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(pFormat[i].index, pFormat[i].size, pFormat[i].type,
       pFormat[i].normalized, pFormat[i].stride, pFormat[i].offsetPointer);
  }
}

void GLVertexDecleration::bind()
{
  glBindVertexArray(m_VAO);

}

void GLVertexDecleration::destroy()
{
  glDeleteVertexArrays(1,&m_VAO);
}
