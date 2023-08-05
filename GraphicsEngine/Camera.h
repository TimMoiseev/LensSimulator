#pragma once
#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
using vec3 = glm::vec3;
using mat4 = glm::mat4;
class Camera
{
	vec3 position;
	vec3 target;
	float fovy;
	float aspect;
	float zNear;
	float zFar;
	mat4 cameraMatrix;
	mat4 projectionMatrix;
	mat4 viewMatrix;
public:
	Camera(
		vec3 position = vec3(0, 1, 0),
		vec3 target = vec3(0, 0, 0),
		float fovy = glm::radians(45.0f),
		float aspect = 4.0f / 3.0f,
		float zNear = 0.1f,
		float zFar = 100.0f
	);
	Camera() = delete;
	Camera(Camera&) = delete;
	Camera(Camera&&) = delete;
	mat4 getCameraMatrix();
};

