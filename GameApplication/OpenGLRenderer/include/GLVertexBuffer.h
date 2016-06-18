#ifndef _GLVERTEXBUFFER_H
#define _GLVERTEXBUFFER_H

#include "../../include/graphics/VertexBuffer.h"
#include <SDL_opengl.h>

class GLVertexBuffer:public IVertexBuffer
{
public:
  ~GLVertexBuffer();

  bool init(Vertex *pVertex,int numVerts);

  void destroy();

  void bind();

  int getNumberOfVertices()
  {
    return m_numVerts;
  };

private:
  GLVertexBuffer();
private:
  GLuint m_VBO;
  int m_numVerts;
};

#endif
