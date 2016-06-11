#include "GameApplication.h"
#include "utils/Log.h"
#include "graphics/NullRenderer.h"

GameApplication::GameApplication()
{
 	m_pWindow=nullptr;
	m_WindowWidth=640;
	m_WindowHeight=480;
	m_WindowCreationFlags=SDL_WINDOW_OPENGL;
  CREATELOG("log.txt");
}

GameApplication::~GameApplication()
{
  CLOSELOG();
	destroy();
}

void GameApplication::createRenderer(const string& rendererName)
{
  LOG(INFO,"Creating %s",rendererName.c_str());
  //create a null renderer so at least we can exit gracefully
  m_CurrentRenderer=unique_ptr<IRenderer>(new NullRenderer);
  
  auto newRenderer=move(CreateRenderer(m_Options,SDL_GetWindowID(m_pWindow)));
  if (!newRenderer)
  {
    m_CurrentRenderer=move(newRenderer);
  }
}

void GameApplication::createWindow(const string& windowTitle,const unsigned int width, const unsigned int height, const unsigned int windowFlags)
{
  LOG(INFO,"Window Created %s Width -%d Height -%d",windowTitle.c_str(),width,height);
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
}


bool GameApplication::init(int args,char * arg[])
{
  parseConfig(args,arg);
	//ChangeWorkingDirectory();
	//Controls the game loop
	m_bIsRunning = true;

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
  m_CurrentRenderer->begin(vec4(0.0f,0.0f,0.0f,1.0f));

  m_CurrentRenderer->end();
}

void GameApplication::onRenderGUI()
{

}

void GameApplication::destroy()
{
	// clean up, reverse order!!!
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
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
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				//set our boolean which controls the loop to false
				m_bIsRunning = false;
			}
		}
		//init Scene
		update();
		//render
		render();
		//Call swap so that our GL back buffer is displayed

	}
}
