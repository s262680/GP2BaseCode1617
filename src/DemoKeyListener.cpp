#include "DemoKeyListener.h"

DemoKeyListener::DemoKeyListener(GameObject *pObject)
{
  m_pGameObject=pObject;
}

DemoKeyListener::~DemoKeyListener()
{

}

void DemoKeyListener::onKeyDown(SDL_Keycode keyCode)
{
  if (keyCode == SDLK_a)
	{
		m_pGameObject->rotate(vec3(0.0f, -0.1f, 0.0f));
	}else if (keyCode == SDLK_d)
	{
		m_pGameObject->rotate(vec3(0.0f, 0.1f, 0.0f));
	}
	if (keyCode==SDLK_w)
	{
		m_pGameObject->rotate(vec3(-0.1f,0.0f,0.0f));
	}
	else if (keyCode==SDLK_s)
	{
		m_pGameObject->rotate(vec3(0.1f,0.0f,0.0f));
	}
}

void DemoKeyListener::onKeyUp(SDL_Keycode keyCode)
{

}
