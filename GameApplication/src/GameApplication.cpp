#include "GameApplication.h"

GameApplication::GameApplication()
{

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
		//messages have been handled now do our work for the game
		if (m_bIsActive && m_bIsRunning) {
		}
}
