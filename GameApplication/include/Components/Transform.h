#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

class Transform :public BaseComponet
{
public: 
	Transform();
	~Transform();
	void onUpdate();

	mat4& getModelMatrix();

	void setPosition(vec3& pos)
	{
		m_Position = pos;
	};

	void setRotation(vec3& rot)
	{
		m_Rotation = rot;
	};

	void setScale(vec3& scale)
	{
		m_Scale = scale;
	};

	vec3& getPosition()
	{
		return m_Position;
	};

	vec3& getRotation()
	{
		return m_Rotation;
	};

	vec3& getScale()
	{
		return m_Scale;
	};
private:
	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;

	mat4 m_TranslationMatrix;
	mat4 m_ScaleMatrix;
	mat4 m_RotationMatrix;
	mat4 m_RotationXMatrix;
	mat4 m_RotationYMatrix;
	mat4 m_RotationZMatrix;
	mat4 m_Model;
};

#endif