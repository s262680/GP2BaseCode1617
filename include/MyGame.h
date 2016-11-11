#ifndef _MyGame_H
#define _MyGame_H

#include "GameApplication.h"
#include "DemoKeyListener.h"

class MyGame:public GameApplication
{
public:
	MyGame();
	~MyGame();

	void render();
	void update();
	void initScene();
	void destroyScene();
private:
	//matrices
	mat4 m_ViewMatrix;
	mat4 m_ProjMatrix;
	
	shared_ptr<Light> m_Light;
	vec4 m_AmbientLightColour;

	vec3 m_CameraPosition;

	vector<shared_ptr<GameObject> > m_GameObjectList;
};
#endif
