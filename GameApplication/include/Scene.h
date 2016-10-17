#ifndef SCENE_H
#define SCENE_H

#include "Common.h"
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"
#include "Mesh.h"

#include "GameObject.h"

class Scene:public NonCopyable
{
public:
  Scene();
  ~Scene();

  void onUpdate();
	void onRender();
	void onInit();
	void onDestroy();
private:
  vector<shared_ptr<GameObject> > m_DisplayList;
};

#endif
