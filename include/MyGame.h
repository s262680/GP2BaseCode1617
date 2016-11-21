#ifndef _MyGame_H
#define _MyGame_H

#include "GameApplication.h"
#include "DemoKeyListener.h"

class MyGame:public GameApplication
{
public:
	MyGame();
	~MyGame();

	void initScene();
};
#endif
