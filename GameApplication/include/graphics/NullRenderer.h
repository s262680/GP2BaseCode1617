#ifndef _NULLRENDERER_H
#define _NULLRENDERER_H

#include "Renderer.h"

class NullRenderer:public IRenderer
{
public:
  NullRenderer(){};
  ~NullRenderer(){};

  bool create(ProgramOptions &options,int windowID)
  {
    return true;
  };

  void begin(const vec4& clearColour)
  {

  };

  void end()
  {

  };

  void destroy()
  {

  };
};
#endif
