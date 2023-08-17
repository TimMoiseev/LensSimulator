#include "pch.h"
#include "Cube.h"

void Cube::createModel(GLfloat A)
{
    vertices->push_back(Vertex({ -A,  -A,  -A }, { 0.0f, 0.0f, 1.0f }));
    vertices->push_back(Vertex({ -A,  +A,  -A }, { 0.0f, 1.0f, 0.0f }));
    vertices->push_back(Vertex({ +A,  -A,  -A }, { 0.0f, 0.0f, 0.6f }));
    vertices->push_back(Vertex({ -A,  -A,  -A }, { 0.0f, 0.0f, 1.0f }));
    vertices->push_back(Vertex({ -A,  +A,  -A }, { 0.0f, 1.0f, 0.0f }));
    vertices->push_back(Vertex({ +A,  +A,  -A }, { 0.0f, 0.0f, 0.6f }));
}

Cube::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat A){
    createModel(A);
    createBuffer(vertices);
}

void Cube::update(float dTime)
{
    objectMatrix = glm::rotate(objectMatrix, glm::radians(0.0000001f * dTime), glm::vec3(0.0f, 0.0f, 1.0f));
}
