#include "Components\Component.h"

BaseComponet::BaseComponet()
{
	m_ParentGameObject = nullptr;
	m_Name = "Component";
}

BaseComponet::~BaseComponet()
{
}

const string & BaseComponet::getName()
{
	return m_Name;
}

void BaseComponet::setName(const string & name)
{
	m_Name = name;
}

void BaseComponet::setParent(shared_ptr<GameObject> gameObject)
{
	m_ParentGameObject = gameObject;
}

shared_ptr<GameObject> BaseComponet::getParent()
{
	return m_ParentGameObject;
}

void BaseComponet::onUpdate()
{
}

void BaseComponet::onRender()
{
}

void BaseComponet::onInit()
{
}

void BaseComponet::onDestroy()
{
}
