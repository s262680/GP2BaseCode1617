#ifndef _GAMEAPPLICATION_H
#define _GAMEAPPLICATION_H

#include "Common.h"
#include "CommandLineParser.h"
#include "XMLOptionsParser.h"
#include "ProgramOptions.h"
#include "../Utils/include/NonCopyable.h"
#include "graphics/Renderer.h"

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

	//This is where a scene is initialised, this assumes we only have one scene
	//we should probably create some sort of SceneManager class to manage more than one
	//scene
	virtual void initScene();

	//This updates the current frame of the game, this will call each subsystem in
	//turn and everything in the game should be up to date
	virtual void update();

	//render the current frame of the game
	virtual void render();

	//called when we have to render a GUI, we are using IMGUI for ease of use
	//we should really create our own retained GUI system
	virtual void onRenderGUI();

	//called when we want to destroy the game, this will delete all major
	//subsystem in reverse order
	virtual void OnQuit();

	//Basically runs our game
	void run();

	void createWindow(const string& windowTitle,const unsigned int width, const unsigned int height, const unsigned int windowFlags=0);
	void createRenderer(const string& rendererName);
protected:
	//SDL Windows
	SDL_Window * m_pWindow;
	//SDL Drawing Context
	//SDL_GLContext m_glcontext;
	bool m_bIsRunning;

	unsigned int m_WindowWidth;
	unsigned int m_WindowHeight;
	unsigned int m_WindowCreationFlags;

	ProgramOptions m_Options;

	void parseConfig(int args,char * arg[]);

	unique_ptr<IRenderer> m_CurrentRenderer;
};
#endif
