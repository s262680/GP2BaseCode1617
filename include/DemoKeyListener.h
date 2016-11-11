#ifndef DEMOKEYLISTENER_H
#define DEMOKEYLISTENER_H

#include "GameObject.h"
#include "KeyboardListener.h"

class DemoKeyListener:public IKeyboardListener
{
public:
  DemoKeyListener(GameObject *pObject);
  ~DemoKeyListener();

  void onKeyDown(SDL_Keycode keyCode);
  void onKeyUp(SDL_Keycode keyCode);
private:
  GameObject *m_pGameObject;
};

#endif
