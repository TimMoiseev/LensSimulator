#pragma once
#include "Buffer.h"
class VertexBuffer :
    public Buffer
{
public:
    
    VertexBuffer(GLuint size, const void* data);
    ~VertexBuffer();
    const void* data;
};

enum VertexType {
    Coordinate = 1,
    Color = 2,
    Normal = 4
};

inline VertexType operator|(VertexType a, VertexType b) {
    return static_cast<VertexType>(static_cast<int>(a) | static_cast<int>(b));
}