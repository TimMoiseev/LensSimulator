#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
out vec4 vColor;
uniform mat4 cameraMatrix;
uniform mat4 objectMatrix;
void main(){
    gl_Position = cameraMatrix * (objectMatrix * vec4(aPos, 1.0));
    vColor = vec4(aColor, 0.9);
 }