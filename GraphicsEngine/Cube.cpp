#include "pch.h"
#include "Cube.h"

void Cube::createModel()
{
    /*
           7 ___________. 6
            /.         /.
           / .        / .
         3/__________/ 2.
          |  .       |  .
          |4 . . . . |. . 5
          | .        | /
          |__________|/
         0          1
    */
    vertices->push_back(Vertex({ -a,  -a,  -a }, { 0.0f, 0.0f, 1.0f }));//0
    vertices->push_back(Vertex({ +a,  -a,  -a }, { 0.0f, 0.0f, 0.0f }));//1
    vertices->push_back(Vertex({ +a,  +a,  -a }, { 0.0f, 0.0f, 0.0f }));//2
    vertices->push_back(Vertex({ -a,  +a,  -a }, { 0.0f, 0.0f, 0.0f }));//3

    vertices->push_back(Vertex({ -a,  -a,  +a }, { 0.0f, 0.0f, 0.0f }));//4
    vertices->push_back(Vertex({ +a,  -a,  +a }, { 0.0f, 0.0f, 0.0f }));//5
    vertices->push_back(Vertex({ +a,  +a,  +a }, { 0.0f, 1.0f, 0.0f }));//6
    vertices->push_back(Vertex({ -a,  +a,  +a }, { 0.0f, 0.0f, 0.0f }));//7

    indices->push_back(1);
    indices->push_back(0);
    indices->push_back(3);
    indices->push_back(3);
    indices->push_back(2);
    indices->push_back(1);

    indices->push_back(4);
    indices->push_back(5);
    indices->push_back(7);
    indices->push_back(5);
    indices->push_back(7);
    indices->push_back(6);

    indices->push_back(2);
    indices->push_back(3);
    indices->push_back(7);
    indices->push_back(2);
    indices->push_back(6);
    indices->push_back(7);

    indices->push_back(0);
    indices->push_back(1);
    indices->push_back(5);
    indices->push_back(0);
    indices->push_back(4);
    indices->push_back(5);

    indices->push_back(1);
    indices->push_back(2);
    indices->push_back(5);
    indices->push_back(2);
    indices->push_back(5);
    indices->push_back(6);

    indices->push_back(0);
    indices->push_back(3);
    indices->push_back(4);
    indices->push_back(3);
    indices->push_back(4);
    indices->push_back(7);
}

Cube::Cube(GLfloat A, GLfloat x, GLfloat y, GLfloat z) : a{ A }, x{ x }, y{ y }, z{ z } {
    createModel();
    translate(glm::vec3(x, y, z));
    createBuffer(vertices, indices);
}

void Cube::update(float dTime)
{
    delete indices;
    delete vertices;
    a += 0.00000001f * dTime;
    vertices = new std::vector<Vertex>();
    indices = new std::vector<GLuint>();
    createModel();
    createBuffer(vertices, indices);
}
