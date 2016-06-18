#ifndef _VERTEXBUFFER_H
#define _VERTEXBUFFER_H

#include "Vertex.h"

class IVertexBuffer
{
public:
  virtual ~IVertexBuffer(){};

  virtual bool init(Vertex *pVertex,int numVerts)=0;

  virtual void destroy()=0;

  virtual void bind()=0;

  virtual int getNumberOfVertices()=0;
};

#endif
