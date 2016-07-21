#ifndef _VERTEXDECLERATION_H
#define _VERTEXDECLERATION_H

#include "VertexFormat.h"

class IVertexDecleration
{
public:
    IVertexDecleration();
    virtual ~IVertexDecleration(){};

    virtual void setVeretxFormat(VertexFormat *pFormat)=0;

    virtual void bind()=0;
};

#endif
