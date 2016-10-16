#include "Components/Transform.h"

Transform::Transform()
{
	m_Position=vec3(0.0f,0.0f,0.0f);
	m_Rotation=vec3(0.0f,0.0f,0.0f);
	m_Scale=vec3(1.0f,1.0f,1.0f);

	m_Model=mat4(1.0f);
	m_TranslationMatrix = mat4(1.0f);
	m_ScaleMatrix = mat4(1.0f);

	m_RotationMatrix = mat4(1.0f);
	m_RotationXMatrix = mat4(1.0f);
	m_RotationYMatrix = mat4(1.0f);
	m_RotationZMatrix = mat4(1.0f);
	m_Name = "Transform";
}

Transform::~Transform()
{
}

void Transform::onUpdate()
{
	m_RotationXMatrix = rotate(radians(m_Rotation.x), vec3(1.0f, 0.0f, 0.0f));
	m_RotationYMatrix = rotate(radians(m_Rotation.y), vec3(0.0f, 1.0f, 0.0f));
	m_RotationZMatrix = rotate(radians(m_Rotation.z), vec3(0.0f, 0.0f, 1.0f));
	m_RotationMatrix = m_RotationXMatrix*m_RotationYMatrix*m_RotationZMatrix;

	m_ScaleMatrix=scale(m_Scale);

	m_TranslationMatrix = translate(m_Position);

	m_Model = m_TranslationMatrix*m_RotationMatrix*m_ScaleMatrix;
}

mat4 & Transform::getModelMatrix()
{
	return m_Model;
}
