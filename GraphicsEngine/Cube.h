#pragma once
#include "Scene.h"
#include "Primitive.h"
class Cube :
    public Primitive
{
    void createModel() override;
    
    GLfloat a;
    GLfloat x;
    GLfloat y;
    GLfloat z;
public:
    Cube(GLfloat A = 0.25f, GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);
    void update(float dTime) override;

};

