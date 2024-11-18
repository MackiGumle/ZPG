#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <list>


enum lightType {
	POINT_LIGHT,
	DIRECTIONAL_LIGHT,
	SPOT_LIGHT
};

class BaseLight {
public:
	BaseLight(glm::vec3 position = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float constant = 1.0f, float linear = 0.2f, float quadratic = 0.0f);
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	float constant;
	float linear;
	float quadratic;

private:
};

class PointLight : public BaseLight {
public:
	PointLight(glm::vec3 position = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float constant = 1.0f, float linear = 0.2f, float quadratic = 0.0f);

private:
};

class DirectionalLight : public BaseLight {
public:
	DirectionalLight(glm::vec3 direction, glm::vec3 position = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float constant = 1.0f, float linear = 0.2f, float quadratic = 0.0f);
	glm::vec3 direction;

private:
};

class SpotLight : public BaseLight {
public:
	SpotLight(float angle = 15.5f, glm::vec3 direction = glm::vec3(0.0f), glm::vec3 position = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float constant = 1.0f, float linear = 0.2f, float quadratic = 0.0f);
	glm::vec3 direction;
	float angle;

private:
};

