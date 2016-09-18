#include "GameApplication.h"

GameApplication::GameApplication()
{
 	m_pWindow=nullptr;
	m_WindowWidth=640;
	m_WindowHeight=480;
	m_WindowCreationFlags=0;
	CREATELOG("log.txt");
	m_bIsActive=false;
	m_bIsRunning=false;
}

GameApplication::~GameApplication()
{
  CLOSELOG();
}

void GameApplication::createWindow(const string& windowTitle,const unsigned int width, const unsigned int height, const unsigned int windowFlags)
{
  LOG(INFO,"Window Created %s Width - %d Height - %d",windowTitle.c_str(),width,height);
	//Create a window
	m_pWindow = SDL_CreateWindow(
		windowTitle.c_str(),             // window title
		SDL_WINDOWPOS_CENTERED,     // x position, centered
		SDL_WINDOWPOS_CENTERED,     // y position, centered
		width,                        // width, in pixels
		height,                        // height, in pixels
		windowFlags           // flags
		);

		m_WindowWidth=width;
		m_WindowHeight=height;
}

void GameApplication::parseConfig(int args,char * arg[])
{
  stringstream ss;
  //parse config file
  XMLOptionsParser xmlParser=XMLOptionsParser("settings.xml");
  xmlParser.parse(m_Options);
  ss<<m_Options;
  LOG(INFO,"Settings Parsed\n%s",ss.str().c_str());
  ss.str( std::string());
  ss.clear();
	//parse command line arguments into keyvalue pairs, this should
	//overide options in config files
  CommandLineParser commandLineParser=CommandLineParser(args,arg);
  commandLineParser.parse(m_Options);
  ss<<m_Options;
  LOG(INFO,"Command Line Parsed\n%s",ss.str().c_str());
  ss.str( std::string());
  ss.clear();
}


bool GameApplication::init(int args,char * arg[])
{
  parseConfig(args,arg);

	//Controls the game loop
	m_bIsRunning = true;

  LOG(INFO,"%s","Initialising SDL");
	// init everyting - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		//std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;
    LOG(ERROR,"SDL can't be initialised %s",SDL_GetError());
		return false;
	}

	m_WindowWidth=m_Options.getOptionAsInt("WindowWidth");
	m_WindowHeight=m_Options.getOptionAsInt("WindowHeight");

	createWindow(m_Options.getOption("WindowTitle"),m_WindowWidth,m_WindowHeight,m_WindowCreationFlags);


	//Init Scene
	initScene();

	m_bIsActive=true;
	return true;
}

void GameApplication::initScene()
{
}


void GameApplication::OnQuit()
{
	//set our boolean which controls the loop to false
	m_bIsRunning = false;
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void GameApplication::OnMaximize()
{
  LOG(INFO,"%s","Maximize");
}

void GameApplication::OnMinimize()
{
  LOG(INFO,"%s","Minimize");
  m_bIsActive=false;
}

void GameApplication::OnRestored()
{
  LOG(INFO,"%s","Restored");
  m_bIsActive=true;
}

void GameApplication::run()
{
	SDL_Event event;
	//Game Loop
	while (m_bIsRunning)
	{
		//While we still have events in the queue
		while (SDL_PollEvent(&event)) {
			//Get event type
			if (event.type == SDL_QUIT) {

				OnQuit();
			}
			if (event.type == SDL_WINDOWEVENT)
			{
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
				{
					OnQuit();
					break;
				}

				case SDL_WINDOWEVENT_MINIMIZED:
				{
					OnMinimize();
					break;
				}

				case SDL_WINDOWEVENT_MAXIMIZED:
				{
					OnMaximize();
					break;
				}
				case SDL_WINDOWEVENT_RESTORED:
				{
					OnRestored();
					break;
				}
				}
			}
		}
		//messages have been handled now do our work for the game
		if (m_bIsActive && m_bIsRunning) {
		}
	}
}
