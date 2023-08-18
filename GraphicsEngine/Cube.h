#pragma once
#include "Scene.h"
class Cube :
    public Scene
{
    void createModel(GLfloat A);
    std::vector<Vertex>* vertices = new std::vector<Vertex>();
    std::vector<GLuint>* indices = new std::vector<GLuint>();
    GLfloat a;
public:
    Cube(GLfloat A = 0.25f);
    void update(float dTime) override;

};

