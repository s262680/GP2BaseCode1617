#ifndef _VERTEXFORMAT_H
#define _VERTEXFORMAT_H

//Based on OpenGL, may have to be shifted if
//moving to other renderers
enum VertexFormatType
{
  BYTE=0x1400,
  UNSIGNED_BYTE=0x1401,
  SHORT=0x1402,
  UNSIGNED_SHORT=0x1403,
  INT=0x1404,
  UNSIGNED_INT=0x1405,
  FLOAT=0x1406,
  DOUBLE=0x140A,
};

struct VertexFormat
{
  unsigned int index;
  int size;
  VertexFormatType type;
  //BYTES, SHORTS mapped to float (0-1)?
  int normalized;
  int stride;
  //this may change
  void * offsetPointer;
};

#endif
