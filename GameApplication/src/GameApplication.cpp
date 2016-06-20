#include "GameApplication.h"
#include "../Utils/include/Log.h"
#include "graphics/NullRenderer.h"
#include "../OpenGLRenderer/include/OpenGLRenderer.h"

GameApplication::GameApplication()
{
 	m_pWindow=nullptr;
	m_WindowWidth=640;
	m_WindowHeight=480;
	m_WindowCreationFlags=SDL_WINDOW_OPENGL;
  CREATELOG("log.txt");
  m_bIsActive=false;
  m_bIsRunning=false;
  m_Lag=0.0f;
  m_UpdateRate=1.0f/60.0f;
}

GameApplication::~GameApplication()
{
  CLOSELOG();
}

void GameApplication::createRenderer(const string& rendererName)
{
  LOG(INFO,"Creating %s",rendererName.c_str());
  //create a null renderer so at least we can exit gracefully
  m_CurrentRenderer=unique_ptr<IRenderer>(new NullRenderer);

  auto newRenderer=unique_ptr<IRenderer>(new OpenGLRenderer);
  if (newRenderer->create(m_Options,SDL_GetWindowID(m_pWindow)))
  {
    m_CurrentRenderer=move(newRenderer);
  }
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

	//Initialise SDL Image
	int	imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int	returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)&	(imageInitFlags)) != imageInitFlags)	{
    LOG(ERROR,"SDL Image Can't be Initialised %s",IMG_GetError());
		return false;
	}

	//Initialise SDL TTF
	if (TTF_Init() == -1)	{
    LOG(ERROR,"SDL TTF Can't be Initialised %s",TTF_GetError());
		return false;
	}
  m_WindowWidth=m_Options.getOptionAsInt("WindowWidth");
  m_WindowHeight=m_Options.getOptionAsInt("WindowHeight");

	createWindow(m_Options.getOption("WindowTitle"),m_WindowWidth,m_WindowHeight,m_WindowCreationFlags);

  createRenderer(m_Options.getOption("RendererName"));

  //Init Scene
	initScene();

  m_bIsActive=true;
  m_Timer.start();
	return true;
}

void GameApplication::initScene()
{
}

void GameApplication::update()
{

}

void GameApplication::render()
{
  m_CurrentRenderer->begin(vec4(1.0f,0.0f,0.0f,1.0f));

  m_CurrentRenderer->end();
}

void GameApplication::onRenderGUI()
{

}

void GameApplication::OnQuit()
{
  //set our boolean which controls the loop to false
  m_bIsRunning = false;
	// clean up, reverse order!!!
  m_CurrentRenderer->destroy();
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	TTF_Quit();
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
      if (event.type==SDL_WINDOWEVENT)
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
    if (m_bIsActive && m_bIsRunning){
      m_Timer.update();

      m_Lag+=m_Timer.getDeltaTime();
      //process input
      while (m_Lag>=m_UpdateRate)
      {
          update();
          m_Lag-=m_UpdateRate;
      }
		  //render
		  render();
    }

	}
}
