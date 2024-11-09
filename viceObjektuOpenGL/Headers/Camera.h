#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <list>
#include <GLFW/glfw3.h>
#include "ObserverPattern.h"


class Camera : public Subject
{
public:
	Camera(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

	void move(std::unordered_map<int, bool>& keys);

	//void move(int direction);
	void rotate(float xoffset, float yoffset, bool constrainPitch = true);

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	glm::vec3 getPosition() const;

	void setProjectionMatrix(float fov, float aspect,
		float near = 0.01f, float far = 200.0f);

private:
	void updateCameraVectors();

	glm::vec3 position;
	glm::vec3 front;
	// actually pointing in the reverse direction of target. 
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	float yaw;
	float pitch;
	float movementSpeed;
	float mouseSensitivity;
};

