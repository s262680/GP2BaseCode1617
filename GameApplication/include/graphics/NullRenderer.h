#ifndef _NULLRENDERER_H
#define _NULLRENDERER_H

#include "Renderer.h"

class NullRenderer:public IRenderer
{
public:
  NullRenderer(){};
  ~NullRenderer(){};

  bool create(ProgramOptions &options,int windowID)
  {
    return true;
  };

  void begin(const vec4& clearColour)
  {

  };

  void end()
  {

  };

  void destroy()
  {

  };

  shared_ptr<IVertexBuffer> createVertexBuffer(Vertex *pVertex,int numVerts)
  {
    return nullptr;
  };

  shared_ptr<IIndexBuffer> createIndexBuffer(int *pIndices, int numIndices)
  {
    return nullptr;
  };

  shared_ptr<IVertexDecleration> createVertexDecleration(VertexFormat *pFormat, int count)
  {
    return nullptr;
  };
};
#endif
