#indef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "../GameApplication/include/Renderer.h"
#include "../GameApplication/include/untils/NonCopyable.h"

class OpenGLRenderer:public NonCopyable, IRenderer
{
public:
  OpenGLRenderer();
  ~OpenGLRenderer();

  bool create(ProgramOptions &options);
  void begin(vec4& clearColour);
  void end();
};

#endif
