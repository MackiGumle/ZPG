#include "Application.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>


Camera::Camera(glm::vec3 position, glm::vec3 up)
	: position(position), front(glm::vec3(0.0f, 0.0f, 0.0f)), fov(60.0f), yaw(-90.0f), pitch(0.0f), movementSpeed(10.0f), mouseSensitivity(0.1f)
{
	worldUp = up;

	viewMatrix = glm::lookAt(position, position + front, up);
	projectionMatrix = glm::perspective(glm::radians(fov), Application::getWidth() / (float)Application::getHeight(), 0.01f, 500.0f);

	updateCameraVectors();
}

void Camera::move(std::unordered_map<int, bool>& keys)
{
	float cameraSpeed = movementSpeed * Application::getDeltaTime();
	auto oldPosition = position;

	if (keys.at(GLFW_KEY_W))
	{
		position += cameraSpeed * front;
	}
	if (keys.at(GLFW_KEY_S))
	{
		position -= cameraSpeed * front;
	}
	if (keys.at(GLFW_KEY_A))
	{
		position -= right * cameraSpeed;
	}
	if (keys.at(GLFW_KEY_D))
	{
		position += right * cameraSpeed;
	}
	if (keys.at(GLFW_KEY_E))
	{
		position += up * cameraSpeed;
	}
	if (keys.at(GLFW_KEY_Q))
	{
		position -= up * cameraSpeed;
	}

	if (oldPosition != position)
	{
		//std::cout << "[i] Camera moved: " << position.x << " " << position.y << " " << position.z << "\n";
		updateCameraVectors();
	}
}

void Camera::rotate(float xoffset, float yoffset, bool constrainPitch)
{
	if (xoffset == 0 && yoffset == 0)
		return;

	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	//std::cout << "[i] cursor: " << xoffset << " " << yoffset << std::endl;
	//std::cout << "[i] Camera rotated " << yaw << " pitch: " << pitch << "\n";
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}

glm::vec3 Camera::getPosition() const
{
	return position;
}

void Camera::setFov(float fov)
{
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 179.0f)
		fov = 179.0f;

	this->fov = fov;
	setProjectionMatrix(fov, Application::getWidth() / (float)Application::getHeight());
	updateCameraVectors();
}

float Camera::getFov() const
{
	return fov;
}

glm::vec3 Camera::getFront() const
{
	return front;
}

void Camera::setProjectionMatrix(float fov, float aspect, float near, float far)
{
	projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 tmpFront;
	tmpFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	tmpFront.y = sin(glm::radians(pitch));
	tmpFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(tmpFront);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
	viewMatrix = glm::lookAt(position, position + front, up);

	//std::cout << "[i] Camera xyz: " << position.x << "\t" << position.y << "\t" << position.z << std::endl;
	//std::cout << "[i] Camera yaw: " << yaw << "\t" << "pitch: " << pitch << std::endl;

	notifyObservers();
}
