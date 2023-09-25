#pragma once
#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Primitive.h"
#include "HIDInputSystem.h"

using glm::inverse;
using glm::vec4;


class Camera:
	public Primitive
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
		vec3 position = vec3(1, 1, 1),
		vec3 target = vec3(0, 0, 0),
		float fovy = glm::radians(45.0f),
		float aspect = 4.0f / 3.0f,
		float zNear = 0.1f,
		float zFar = 1000.0f
	);
	Camera();
	Camera(Camera&) = delete;
	Camera(Camera&&) = delete;
	void rotate(glm::vec3 axis, GLfloat angle, mat4 matrix);
	void update(float duration) override;
	void update(HIDInputSystem* system);
	mat4 getCameraMatrix();
};

