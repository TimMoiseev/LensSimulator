#pragma once
class VertexBuffer
{
    GLuint size = 0;
    GLuint index = 0;
public:
    const GLuint getIndex() const { return index; };
    VertexBuffer(GLuint size, const void* data);
    ~VertexBuffer();
    
};

enum VertexType {
    Coordinate = 1,
    Color = 2,
    Normal = 4
};

inline VertexType operator|(VertexType a, VertexType b) {
    return static_cast<VertexType>(static_cast<int>(a) | static_cast<int>(b));
}