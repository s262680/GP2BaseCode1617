#ifndef _MyGame_H
#define _MyGame_H

#include "GameApplication.h"

class MyGame:public GameApplication
{
public:
	MyGame();
	~MyGame();

	void update();

	void render();

	void initScene();

	void destroyScene();
private:
	GLuint m_VBO;
	GLuint m_VAO;
};
#endif
