#include "DrawableObject.h"
#include "Lights.h"
#include <iostream>

BaseLight::BaseLight(glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic)
	: position(position), color(color), intensity(intensity), constant(constant), linear(linear), quadratic(quadratic)
{
}

void BaseLight::setObject(DrawableObject* object)
{
	this->object = object;
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic)
	: BaseLight(position, color, intensity, constant, linear, quadratic)
{
}

lightType PointLight::getType() const
{
	return POINT_LIGHT;
}

void PointLight::update()
{
	if (object)
	{
		position = object->getPosition();
	}
}

std::shared_ptr<BaseLight> PointLight::clone() const
{
	return std::make_shared<PointLight>(*this);
}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic)
	: BaseLight(position, color, intensity, constant, linear, quadratic), direction(direction)
{
}

lightType DirectionalLight::getType() const
{
	return DIRECTIONAL_LIGHT;
}

void DirectionalLight::update()
{
}

std::shared_ptr<BaseLight> DirectionalLight::clone() const
{
	return std::make_shared<DirectionalLight>(*this);
}

SpotLight::SpotLight(float angle, glm::vec3 direction, glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic)
	: BaseLight(position, color, intensity, constant, linear, quadratic), direction(direction), angle(glm::radians(angle)), camera(nullptr)
{
}

std::shared_ptr<BaseLight> SpotLight::clone() const
{
	return std::make_shared<SpotLight>(*this);
}

lightType SpotLight::getType() const
{
	return SPOT_LIGHT;
}

void SpotLight::update()
{
	if (camera)
	{
		direction = camera->getFront();
		position = camera->getPosition();
	}
	//std::cout << "[i] SpotLight position: " << position.x << " " << position.y << " " << position.z << "\n";
}

void SpotLight::setCamera(Camera* camera)
{
	this->camera = camera;
}