#include "pch.h"
#include "Camera.h"


Camera::Camera(
	vec3 position, 
	vec3 target,
	float fovy,
	float aspectRatio,
	float zNear,
	float zFar
) : position{ position }, target{ target }, cameraMatrix{}, fovy{ fovy }, aspect{ aspectRatio }, zNear{ zNear }, zFar{ zFar } {
	projectionMatrix = glm::perspective(fovy, aspect, zNear, zFar);
	
	viewMatrix = glm::lookAt(
		position,
		target,
		vec3(0.0, 1.0, 0.0));
	cameraMatrix = projectionMatrix * viewMatrix;
}

mat4 Camera::getCameraMatrix()
{
	return cameraMatrix;
}