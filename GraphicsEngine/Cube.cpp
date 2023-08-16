#include "pch.h"
#include "Cube.h"

std::vector<Vertex>* Cube::createModel(GLfloat A)
{
    //return std::vector<Vertex> {
    //        Vertex({ -A,  -A,  -A }, { 0.0f, 0.0f, 1.0f }), //
    //        Vertex({ -A,  +A,  -A }, { 0.0f, 1.0f, 0.0f }), //AA1B
    //        Vertex({ +A,  -A,  -A }, { 0.0f, 0.0f, 0.6f }),

    //        Vertex({ -A,  -A,  -A }, { 0.0f, 0.0f, 1.0f }),
    //        Vertex({ -A,  +A,  -A }, { 0.0f, 1.0f, 0.0f }), //A1BB1
    //        Vertex({ +A,  +A,  -A }, { 0.0f, 0.0f, 0.6f }),

    //};
    vertices->push_back(Vertex({ -A,  -A,  -A }, { 0.0f, 0.0f, 1.0f }));
    vertices->push_back(Vertex({ -A,  +A,  -A }, { 0.0f, 1.0f, 0.0f }));
    vertices->push_back(Vertex({ +A,  -A,  -A }, { 0.0f, 0.0f, 0.6f }));
    vertices->push_back(Vertex({ -A,  -A,  -A }, { 0.0f, 0.0f, 1.0f }));
    vertices->push_back(Vertex({ -A,  +A,  -A }, { 0.0f, 1.0f, 0.0f }));
    vertices->push_back(Vertex({ +A,  +A,  -A }, { 0.0f, 0.0f, 0.6f }));
    return vertices;
}

Cube::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat A) : Scene(createModel(A > 0 ? A : A = -A)) {
  
}

void Cube::update(float dTime)
{
    objectMatrix = glm::rotate(objectMatrix, glm::radians(0.0000001f * dTime), glm::vec3(0.0f, 0.0f, 1.0f));
}
