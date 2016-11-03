#ifndef _GAMEAPPLICATION_H
#define _GAMEAPPLICATION_H

#include "Common.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "ModelLoading.h"

//Game Application class, this basically wraps up the initialisation of a game
//this will be the base class of any game we are making. You should override this
//and some of the methods to create your own game
class GameApplication:public NonCopyable
{
public:
	//Constructor
	GameApplication();
	//Virtual Deconstructor
	virtual ~GameApplication();

	//This is where all major subsystems are created
	virtual bool init(int args,char * arg[]);

	//called when we want to destroy the game, this will delete all major
	//subsystem in reverse order
	virtual void OnQuit();

	virtual void OnMaximize();

	virtual void OnMinimize();

	virtual void OnRestored();

	virtual void update();

	virtual void render();

	virtual void initScene();
	virtual void destroyScene();

	void OnBeginRender();
	void OnEndRender();
	void setViewport( int width, int height );

	//Basically runs our game
	void run();

	void createWindow(const string& windowTitle,const unsigned int width, const unsigned int height, const unsigned int windowFlags=0);
	void initGraphics();
protected:
	//SDL Windows
	SDL_Window * m_pWindow;
	SDL_GLContext m_GLcontext;

	bool m_bIsRunning;
	bool m_bIsActive;

	unsigned int m_WindowWidth;
	unsigned int m_WindowHeight;
	unsigned int m_WindowCreationFlags;

	ProgramOptions m_Options;

	void parseConfig(int args,char * arg[]);
};
#endif
