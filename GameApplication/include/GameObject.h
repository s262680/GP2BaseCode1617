#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common.h"

#include "Components\Component.h"
#include "Components\Transform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void onUpdate();
	void onRender();
	void onInit();
	void onDestroy();

	void addComponent(shared_ptr<IComponent> component);
	void addChild(shared_ptr<GameObject> gameobject);

	template<class type>
	type getComponent()
	{
		for (auto component : m_Components)
		{
			if (typeid(component) == typeid(type))
			{
				return (type)component;
			}
		}
	};
private:
	vector<shared_ptr<IComponent> > m_Components;
	vector<shared_ptr<GameObject> > m_ChildrenGameObjects;

};

#endif
