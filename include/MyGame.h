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

	GLuint m_Texture;
	GLuint m_Sampler;
private:
	GLuint m_VBO;
	GLuint m_VAO;
	GLuint m_ShaderProgram;

	mat4 m_ViewMatrix;
	mat4 m_ProjMatrix;
	mat4 m_ModelMatrix;
};
#endif
