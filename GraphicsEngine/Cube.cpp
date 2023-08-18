#include "pch.h"
#include "Cube.h"

void Cube::createModel(GLfloat A)
{
    
    /*
      7 ___________.  6
       /.         /.
      / .        / .
    3/__________/ 2.
     |  .       |  .
     |4 . . . . |. . 5
     | .        | /
     |__________|/
    0          1
    */
    vertices->push_back(Vertex({ -A,  -A,  -A }, { 0.0f, 0.0f, 1.0f }));//0
    vertices->push_back(Vertex({ +A,  -A,  -A }, { 0.0f, 1.0f, 0.0f }));//1
    vertices->push_back(Vertex({ +A,  +A,  -A }, { 0.0f, 0.0f, 0.6f }));//2
    vertices->push_back(Vertex({ -A,  +A,  -A }, { 0.0f, 0.0f, 1.0f }));//3

    vertices->push_back(Vertex({ -A,  -A,  +A }, { 0.0f, 0.0f, 1.0f }));//4
    vertices->push_back(Vertex({ +A,  -A,  +A }, { 0.0f, 1.0f, 0.0f }));//5
    vertices->push_back(Vertex({ +A,  +A,  +A }, { 0.0f, 0.0f, 0.6f }));//6
    vertices->push_back(Vertex({ -A,  +A,  +A }, { 0.0f, 0.0f, 1.0f }));//7

    indices->push_back(0);
    indices->push_back(1);
    indices->push_back(2);
    indices->push_back(0);
    indices->push_back(2);
    indices->push_back(3);
}

Cube::Cube(GLfloat A) : a{ A } {
    createModel(A);
    createBuffer(vertices, indices);
}

void Cube::update(float dTime)
{
    objectMatrix = glm::rotate(objectMatrix, glm::radians(0.0000001f * dTime*(float)a), glm::vec3(0.0f, 0.0f, 1.0f));
}
