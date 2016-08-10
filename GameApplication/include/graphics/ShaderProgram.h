#ifndef _SHADERPROGRAM_H
#define _SHADERPROGRAM_H

#include "../Common.h"

class IShader
{
public:
  virtual ~IShader(){};
};

class IShaderProgram
{
public:
  virtual ~IShaderProgram(){};

  virtual void setVertexShader(shared_ptr<IShader> pShader)=0;
  virtual void setGeometryShader(shared_ptr<IShader> pShader)=0;
  virtual void setFragmentShader(shared_ptr<IShader> pShader)=0;

  //set stuff
  virtual void setFloat(string& name, float f)=0;
  virtual void setInt(string& name,int i)=0
  virtual void setVec2(string& name,vec2 &v)=0;
  virtual void setVec3(string& name,vec3 &v)=0;
  virtual void setVec4(string& name,vec4 &v)=0;
  virtual void setMat3(string& name,mat3 &m)=0;
  virtual void setMat4(string& name,mat4 &m)=0;
  virtual bool link()=0;

  //Uniform Buffers(AKA blocks)
  //https://www.opengl.org/wiki/Uniform_Buffer_Object
};
#endif
