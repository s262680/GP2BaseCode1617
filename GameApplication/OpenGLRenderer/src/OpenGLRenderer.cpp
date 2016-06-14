#include "OpenGLRenderer.h"
#include "../../Utils/include/Log.h"

ostream& operator<<(ostream& os, const OpenGLVersion& version)
{
	os << "GL_VERSION_" << version.major << "_" << version.minor;
	return os;
}

OpenGLRenderer::OpenGLRenderer()
{

}

OpenGLRenderer::~OpenGLRenderer()
{

}

void OpenGLRenderer::destroy()
{
  SDL_GL_DeleteContext(m_Context);
}

string OpenGLRenderer::getCapsAsString()
{
	stringstream stringStream;

	stringStream << "OpenGl Version: " << glGetString(GL_VERSION)<<"\n";
	stringStream << "Vendor: " << glGetString(GL_VENDOR) << "\n";
	stringStream << "Renderer: " << glGetString(GL_RENDERER) << "\n";
	stringStream << "Shading: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
	stringStream << "Extensions Supported\n";
	GLint n = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	for(GLint i = 0; i<n; i++)
	{
		const char* extension =
			(const char*)glGetStringi(GL_EXTENSIONS, i);
		stringStream << extension << ", ";
	}

	return stringStream.str();
}

bool OpenGLRenderer::create(ProgramOptions &options,int windowID)
{
	LOG(INFO,"%s","Determing OpenGL Version");
	//lets create the lowest context we can
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	//Create a dummy window, in windows we can create two contexts on a window
	//on mac we need to create this hidden dummy window!
	SDL_Window * dummyWindow = SDL_CreateWindow(
		"DummyWindow",             // window title
		SDL_WINDOWPOS_CENTERED,     // x position, centered
		SDL_WINDOWPOS_CENTERED,     // y position, centered
		640,                        // width, in pixels
		480,                        // height, in pixels
		SDL_WINDOW_OPENGL|SDL_WINDOW_HIDDEN          // flags
		);
	// Create a dummy OpenGL context associated with the dummy window.
	SDL_GLContext dummyContext = SDL_GL_CreateContext(dummyWindow);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
      //Problem: glewInit failed, something is seriously wrong.
      //LOG(ERROR,"GLEW Error: %s",glewGetErrorString(err));

  }

	SDL_GL_DeleteContext(dummyContext);
	SDL_DestroyWindow(dummyWindow);

  OpenGLVersion bestOGLVersion=getBestGLVersion();

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, bestOGLVersion.major);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, bestOGLVersion.minor);

  m_CachedWindow=SDL_GetWindowFromID(windowID);
  m_Context = SDL_GL_CreateContext(m_CachedWindow);
  if (!m_Context)
  {
    LOG(ERROR,"Can't Create OpenGL Context %s",SDL_GetError());
  }

  LOG(INFO,"%s",getCapsAsString().c_str());


  return true;
}

OpenGLVersion OpenGLRenderer::getBestGLVersion()
{
  int supportedIndex = 0;
  stringstream stringStream;
  for (int i = 0; i < sizeof(SupportedOGLVersions)/sizeof(OpenGLVersion); i++)
  {
    stringStream.str("");
    supportedIndex = i;
    stringStream << SupportedOGLVersions[i];
    if (glewIsSupported(stringStream.str().c_str()))
    {
      break;
    }
  }

  return SupportedOGLVersions[supportedIndex];
}

void OpenGLRenderer::begin(const vec4& clearColour)
{
  //Set the clear colour(background)
	glClearColor(clearColour.r, clearColour.g, clearColour.b, clearColour.a);
	//Clear the depth buffer
	glClearDepth(1.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::end()
{
  SDL_GL_SwapWindow(m_CachedWindow);
}
