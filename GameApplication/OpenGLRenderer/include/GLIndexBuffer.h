#ifndef _GLINDEXBUFFER_H
#define _GLINDEXBUFFER_H

#include "../../include/graphics/IndexBuffer.h"
#include <GL/glew.h>
#include <SDL_opengl.h>

class GLIndexBuffer
{
public:
  GLIndexBuffer();
  ~GLIndexBuffer();

  bool init(int *pIndices, int numIndices);

  void destroy();

  void bind();

  int getNumberOfIndices()
  {
    return m_numIndices;
  };
private:
  GLuint m_IBO;
  int m_numIndices;
};

#endif
