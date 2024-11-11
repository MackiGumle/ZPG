#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <list>


class BaseLight {
public:
	BaseLight(glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float constant = 1.0f, float linear = 0.2f, float quadratic = 0.0f);
	glm::vec3 Color;
	float intensity;
	float constant;
	float linear;
	float quadratic;
private:

};

class DirectionalLight : public BaseLight {
public:
	
private:
	glm::vec3 Direction;
};

class PointLight : public BaseLight {
public:
	PointLight(glm::vec3 position, glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float constant = 1.0f, float linear = 0.2f, float quadratic = 0.0f);
	glm::vec3 Position;

private:
};
