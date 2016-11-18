#ifndef POSTPROCESSELEMENT_H
#define POSTPROCESSELEMENT_H

#include "Common.h"

class PostProcessElement
{
public:
  PostProcessElement();
  ~PostProcessElement();

  bool create(unsigned int width, unsigned int height);
  void destroy();

  void bind();
  void unbind();

  GLuint GetTexture()
  {
    return m_Texture;
  };
private:
  GLuint m_Texture;
  GLuint m_Sampler;
  GLuint m_DepthBuffer;
  GLuint m_Framebuffer;
};

#endif
