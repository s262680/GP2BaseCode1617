#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common.h"

#include "Components/Component.h"
#include "Components/Transform.h"

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
	type * getComponent()
	{
		type * c = nullptr;
		for (auto component : m_Components)
		{
			c=dynamic_cast<type*>(component.get());
			if (c != nullptr)
				return c;
		}
		return c;
	};

	Transform * getTransform() { return m_Transform; };
private:
	vector<shared_ptr<IComponent> > m_Components;
	vector<shared_ptr<GameObject> > m_ChildrenGameObjects;

	Transform * m_Transform;

};

#endif
