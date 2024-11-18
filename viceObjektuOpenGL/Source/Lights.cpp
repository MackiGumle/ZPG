#include "Lights.h"

BaseLight::BaseLight(glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic)
	: position(position), color(color), intensity(intensity), constant(constant), linear(linear), quadratic(quadratic)
{
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic)
	: BaseLight(position, color, intensity, constant, linear, quadratic)
{
}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic)
	: BaseLight(position, color, intensity, constant, linear, quadratic), direction(direction)
{
}

SpotLight::SpotLight(float angle, glm::vec3 direction, glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic)
	: BaseLight(position, color, intensity, constant, linear, quadratic), direction(direction), angle(angle)
{
}
