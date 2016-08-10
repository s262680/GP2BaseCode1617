#ifndef _VERTEXDECLERATION_H
#define _VERTEXDECLERATION_H

#include "VertexFormat.h"

class IVertexDecleration
{
public:
    virtual ~IVertexDecleration(){};

    virtual void setVertexFormat(VertexFormat *pFormat, int count)=0;

    //probably should be bound by the renderer not by itself!!
    //refactor this shit!
    virtual void bind()=0;
};

#endif
