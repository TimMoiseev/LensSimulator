#include "pch.h"
#include "Camera.h"

Camera::Camera(
	vec3 position, 
	vec3 target,
	float fovy,
	float aspectRatio,
	float zNear,
	float zFar
) : position{ position }, 
target{ target }, 
cameraMatrix{}, 
fovy{ fovy }, 
aspect{ aspectRatio }, 
zNear{ zNear }, 
zFar{ zFar } {
	projectionMatrix = glm::perspective(fovy, aspect, zNear, zFar);
	
	viewMatrix = glm::lookAt(
		position,
		target,
		vec3(1.0, 0.0, 0.0));
	update(0.0f);
}

Camera::Camera()
{
}
void Camera::rotate(glm::vec3 axis, GLfloat angle, mat4 matrix) {
	viewMatrix = glm::rotate(viewMatrix, glm::radians(angle), axis);
}
void Camera::update(float duration)
{

	cameraMatrix = projectionMatrix * viewMatrix;
	rotate(vec3(0.0, 0.0, 1.0), 0.00000001f * duration, viewMatrix);

}

void Camera::update(HIDInputSystem* system)
{
	int dx = 0, dy = 0;
	int zDelta = 0;
	static int oldDx = 0, oldDy = 0;
	int w = 600, h = 400;
	static float angleX = 0;
	static float angleY = 0;
	system->getActualdXdY(dx, dy);
	system->getActualZDelta(zDelta);
	if (zDelta != 0) {
		zDelta > 0 ? (position *= 1.035f) : (position /= 1.035f);
		viewMatrix = glm::lookAt(
			position,
			target,
			vec3(1.0, 0.0, 0.0));
	}
	if (((dx != 0) || (dy != 0)) && ((dx != oldDx) || (dy != oldDy))) {
		auto axisX = vec3(1, 0, 0);
		auto axisY = vec3(0, 1, 0);
		angleX = static_cast<float>(dx) / w;
		angleY = static_cast<float>(dy) / h;
		/*rotate(axisX, angleX, viewMatrix);
		rotate(axisY, angleY, viewMatrix);*/
		/*cameraMatrix = projectionMatrix * viewMatrix;*/
		position = glm::rotateX(position, angleX);
		position = glm::rotateY(position, angleY);
		
		viewMatrix = glm::lookAt(
			position,
			target,
			vec3(1.0, 0.0, 0.0));
		

		oldDx = dx;
		oldDy = dy;

	}
	update(0.0f);
}

mat4 Camera::getCameraMatrix()
{
	return cameraMatrix;
}