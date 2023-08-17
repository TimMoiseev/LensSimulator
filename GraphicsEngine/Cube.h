#pragma once
#include "Scene.h"
class Cube :
    public Scene
{
    void createModel(GLfloat A);
    std::vector<Vertex>* vertices = new std::vector<Vertex>();
public:
    Cube(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f, GLfloat A = 0.25f);
    void update(float dTime) override;

};

