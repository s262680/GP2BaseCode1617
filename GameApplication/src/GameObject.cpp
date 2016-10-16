#include "GameObject.h"

GameObject::GameObject()
{
	shared_ptr<Transform> transformComponent = shared_ptr<Transform>(new Transform());
	addComponent(transformComponent);
	m_Transform = transformComponent.get();

}

GameObject::~GameObject()
{
	
}

void GameObject::onUpdate()
{
	for (auto &gameObject : m_ChildrenGameObjects)
	{
		gameObject->onUpdate();
	}

	for (auto &component : m_Components)
	{
		component->onUpdate();
	}
}

void GameObject::onRender()
{
	for (auto &gameObject : m_ChildrenGameObjects)
	{
		gameObject->onRender();
	}

	for (auto &component : m_Components)
	{
		component->onRender();
	}
}

void GameObject::onInit()
{

	for (auto &gameObject : m_ChildrenGameObjects)
	{
		gameObject->onInit();
	}

	for (auto &component : m_Components)
	{
		component->onInit();
	}
}

void GameObject::onDestroy()
{
	for (auto &gameObject : m_ChildrenGameObjects)
	{
		gameObject->onDestroy();
	}

	for (auto &component : m_Components)
	{
		component->onDestroy();
	}
	m_ChildrenGameObjects.clear();
	m_Components.clear();
}

void GameObject::addComponent(shared_ptr<IComponent> component)
{
	component->setParent(this);
	m_Components.push_back(component);
}

void GameObject::addChild(shared_ptr<GameObject> gameobject)
{
	m_ChildrenGameObjects.push_back(gameobject);
}
