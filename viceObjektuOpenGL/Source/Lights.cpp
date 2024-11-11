#include "Lights.h"

BaseLight::BaseLight(glm::vec3 color, float intensity, float constant, float linear, float quadratic)
	: Color(color), intensity(intensity), constant(constant), linear(linear), quadratic(quadratic)
{
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic)
	: BaseLight(color, intensity, constant, linear, quadratic), Position(position)
{
}