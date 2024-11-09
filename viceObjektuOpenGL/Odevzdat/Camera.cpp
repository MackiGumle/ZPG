#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up)
	: position(position), front(glm::vec3(0.0f, 0.0f, 0.0f)), yaw(-90.0f), pitch(0.0f), movementSpeed(0.5f), mouseSensitivity(0.1f)
{
	/*direction = glm::normalize(position - target);
	right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), direction));
	up = glm::cross(direction, right);*/

	worldUp = up;

	viewMatrix = glm::lookAt(position, position + front, up);
	projectionMatrix = glm::perspective(glm::radians(80.0f), 1920.0f / 1080.0f, 0.01f, 200.0f);
	updateCameraVectors();
}

void Camera::addObserver(ICameraObserver* observer)
{
	//observer->update(viewMatrix, projectionMatrix);
	observers.push_back(observer);
}

void Camera::removeObserver(ICameraObserver* observer)
{
	observers.remove(observer);
}

void Camera::notifyObservers()
{
	for (auto observer : observers)
	{
		observer->update(viewMatrix, projectionMatrix);
	}
}

void Camera::update(std::unordered_map<int, bool>& keys)
{
	if (keys.at(GLFW_KEY_W))
	{
		position += movementSpeed * front;
	}
	if (keys.at(GLFW_KEY_S))
	{
		position -= movementSpeed * front;
	}
	if (keys.at(GLFW_KEY_A))
	{
		position -= right * movementSpeed;
	}
	if (keys.at(GLFW_KEY_D))
	{
		position += right * movementSpeed;
	}

	updateCameraVectors();
}

void Camera::move(int direction)
{
	/*switch (direction)
	{
	case GLFW_KEY_W:
		position += movementSpeed * front;
		break;
	case GLFW_KEY_S:
		position -= movementSpeed * front;
		break;
	case GLFW_KEY_A:
		position -= glm::normalize(glm::cross(front, up)) * movementSpeed;
		break;
	case GLFW_KEY_D:
		position += glm::normalize(glm::cross(front, up)) * movementSpeed;
		break;
	case GLFW_KEY_Q:
		position += glm::normalize(up) * movementSpeed;
		break;
	case GLFW_KEY_E:
		position -= glm::normalize(up) * movementSpeed;
		break;
	}*/

	//std::cout << "[i] Camera Position xyz: " << position.x << "\t" << position.y << "\t" << position.z << std::endl;
}

void Camera::rotate(float xoffset, float yoffset, bool constrainPitch = true)
{
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
	std::cout << "[i] cursor: " << xoffset << " " << yoffset << std::endl;
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 tmpFront;
	tmpFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	tmpFront.y = sin(glm::radians(pitch));
	tmpFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(tmpFront);

	//tmpFront.x = cos(glm::radians(yaw)) * sin(glm::radians(pitch));
	//tmpFront.y = cos(glm::radians(pitch));
	//tmpFront.z = sin(glm::radians(yaw)) * sin(glm::radians(pitch));

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
	viewMatrix = glm::lookAt(position, position + front, up);

	std::cout << "[i] Camera xyz: " << position.x << "\t" << position.y << "\t" << position.z << std::endl;
	std::cout << "[i] Camera yaw: " << yaw << "\t" << "pitch: " << pitch << std::endl;
	notifyObservers();
}