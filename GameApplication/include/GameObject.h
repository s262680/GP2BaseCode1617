
//IF NOT DEFINE, THEN DEFINE IT
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common.h"
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"


//TO DO: need to add function to change position, rotation and scale

class GameObject
{
public:
	GameObject();
	//~mean Deconstructor
	~GameObject();


	//& mean passing by reference, address, its just a integer
	void onRender(mat4& view, mat4& projection);
	void onUpdate();
	void onInit();
	void onDestroy();

	void loadTexture(const string& filename);
	void loadShaders(const string& vsFilename, const string& fsFilename);
	void copyVertexData(Vertex*pVertex, int numberOfVertices);

	


private:
	GLuint m_VBO;
	GLuint m_VAO;

	//Shader Program
	GLuint m_ShaderProgram;

	mat4 m_ModelMatrix;

	GLuint m_Texture;
	GLuint m_ClampSampler;

	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;

	mat4 m_TranslationMatrix;
	mat4 m_RotationMatrix;
	mat4 m_ScaleMatrix;

	int m_NumberOfVerts;

protected:

};




#endif
