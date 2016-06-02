#include "GameApplication.h"

GameApplication::GameApplication()
{
 	m_pWindow=nullptr;
	m_WindowWidth=640;
	m_WindowHeight=480;
	m_WindowCreationFlags=0;
}

GameApplication::~GameApplication()
{
	destroy();
}

void GameApplication::createWindow(const string& windowTitle,const unsigned int width, const unsigned int height, const unsigned int windowFlags)
{
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

bool GameApplication::init()
{
	//ChangeWorkingDirectory();
	//Controls the game loop
	m_bIsRunning = true;

	// init everyting - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;

		return false;
	}

	//Initialise SDL Image
	int	imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int	returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)&	(imageInitFlags)) != imageInitFlags)	{

		cout << "ERROR	SDL_Image	Init	" << IMG_GetError() << endl;
		return false;
	}

	//Initialise SDL TTF
	if (TTF_Init() == -1)	{
		std::cout << "ERROR	TTF_Init:	" << TTF_GetError();
		return false;
	}

	createWindow("GP2BaseCode",m_WindowWidth,m_WindowHeight,m_WindowCreationFlags);
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
