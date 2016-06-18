#ifndef _RENDERER_H
#define _RENDERER_H

#include "../Common.h"
#include "../ProgramOptions.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class IRenderer
{
public:
  virtual ~IRenderer(){};
  virtual bool create(ProgramOptions &options,int windowID)=0;
  virtual void begin(const vec4& clearColour)=0;
  virtual void end()=0;
  virtual void destroy()=0;

  virtual shared_ptr<IVertexBuffer> createVertexBuffer(Vertex *pVertex,int numVerts)=0;
  virtual shared_ptr<IIndexBuffer> createIndexBuffer(int *pIndices, int numIndices)=0;
};

#endif
