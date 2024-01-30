#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;
out vec4 vColor;
out vec3 normal;
out vec3 fragPos;
uniform mat4 cameraMatrix;
uniform mat4 objectMatrix;
void main(){
    gl_Position = cameraMatrix * (objectMatrix * vec4(aPos, 1.0));
    vec4 p = objectMatrix * vec4(aPos, 1.0);
    fragPos = vec3(p.x, p.y, p.z);
    vColor = vec4(aColor, 1.0);
    normal = aNormal;
 }