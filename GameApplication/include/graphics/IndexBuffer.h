#ifndef _INDEXBUFFER_H
#define _INDEXBUFFER_H

class IIndexBuffer
{
public:
  virtual ~IIndexBuffer(){};

  virtual bool init(int *pIndices, int numIndices)=0;

  virtual void destroy()=0;

  virtual void bind()=0;
};

#endif
