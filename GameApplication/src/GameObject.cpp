#include "GameObject.h"

GameObject::GameObject()
{
	m_VBO = 0;
	m_VAO = 0;
	m_ShaderProgram = 0;

	m_Texture = 0;
	m_ClampSampler = 0;

	m_Position = vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = vec3(0.0f, 0.0f, 0.0f);
	m_Scale = vec3(1.0f, 1.0f, 1.0f);

	m_ModelMatrix = mat4(1.0f);
	m_TranslationMatrix = mat4(1.0f);
	m_RotationMatrix = mat4(1.0f);
	m_ScaleMatrix = mat4(1.0f);

	m_NumberOfVerts = 0;

}

GameObject::~GameObject()
{
}

void GameObject::onRender(mat4 & view, mat4 & projection)
{
}

void GameObject::onUpdate()
{
	m_RotationMatrix = eulerAngleXYZ(m_Rotation.x, m_Rotation.y, m_Rotation.z);
}

void GameObject::onInit()
{
}

void GameObject::onDestroy()
{
}

void GameObject::loadTexture(const string & filename)
{
}

void GameObject::loadShaders(const string & vsFilename, const string & fsFilename)
{
}

void GameObject::copyVertexData(Vertex * pVertex, int numberOfVertices)
{
}
