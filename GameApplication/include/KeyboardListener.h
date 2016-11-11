#ifndef KEYBOARDLISTENER_H
#define KEYBOARDLISTENER_H

#include <common.h>

class IKeyboardListener
{
public:
  virtual ~IKeyboardListener(){};

  virtual void onKeyDown(SDL_Keycode keyCode)=0;
  virtual void onKeyUp(SDL_Keycode keyCode)=0;
};
#endif
