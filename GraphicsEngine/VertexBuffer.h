#pragma once
#include "Buffer.h"
class VertexBuffer :
    public Buffer
{
    bool colored = false;
public:
    VertexBuffer(const GLfloat* data, const GLfloat* colordata, UINT16 vertexCount, bool colored);
    void bind() override;
};

