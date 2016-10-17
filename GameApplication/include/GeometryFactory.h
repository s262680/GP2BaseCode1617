#ifndef GEOMETRY_FACTORY_H
#define GEOMETRY_FACTORY_H

#include "Common.h"
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"
#include "Mesh.h"

#include "GameObject.h"

class GeometryFactory:public NonCopyable
{
public:
  GeometryFactory(IMeshManager * meshManager);
  ~GeometryFactory();

  
};
#endif
