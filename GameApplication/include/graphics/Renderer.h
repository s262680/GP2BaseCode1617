#ifndef _RENDERER_H
#define _RENDERER_H

#include "../Common.h"
#include "../ProgramOptions.h"

class IRenderer
{
public:
  virtual ~IRenderer(){};
  virtual bool create(ProgramOptions &options,int windowID)=0;
  virtual void begin(const vec4& clearColour)=0;
  virtual void end()=0;
  virtual void destroy()=0;
};

unique_ptr<IRenderer> CreateRenderer(ProgramOptions &options,int windowID);

#endif
