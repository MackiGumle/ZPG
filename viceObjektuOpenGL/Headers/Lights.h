#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <list>
#include "ObserverPattern.h"
#include "Camera.h"



enum lightType {
	POINT_LIGHT,
	DIRECTIONAL_LIGHT,
	SPOT_LIGHT
};

class DrawableObject;
// Observer of Camera
class BaseLight : public Observer {
public:
	// Copy constructor
	BaseLight(const BaseLight& baseLight) = default;
	BaseLight(glm::vec3 position = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float constant = 1.0f, float linear = 0.2f, float quadratic = 0.0f);
	
	virtual void update() = 0;
	virtual std::shared_ptr<BaseLight> clone() const = 0;

	virtual lightType getType() const = 0;

	void setObject(DrawableObject* object);

	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	float constant;
	float linear;
	float quadratic;

protected:
	DrawableObject* object = nullptr;

private:
};

class PointLight : public BaseLight {
public:
	PointLight(const PointLight& pointLight) = default;
	PointLight(glm::vec3 position = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float constant = 1.0f, float linear = 0.2f, float quadratic = 0.0f);
	std::shared_ptr<BaseLight> clone() const override;
	
	lightType getType() const override;

	void update() override;

private:
};

class DirectionalLight : public BaseLight {
public:
	DirectionalLight(const DirectionalLight& directionalLight) = default;
	DirectionalLight(glm::vec3 direction, glm::vec3 position = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float constant = 1.0f, float linear = 0.2f, float quadratic = 0.0f);
	std::shared_ptr<BaseLight> clone() const override;
	
	lightType getType() const override;
	
	void update() override;


	glm::vec3 direction;

private:
};

class SpotLight : public BaseLight {
public:
	SpotLight(const SpotLight& spotLight) = default;
	SpotLight(float angle = 15.5f, glm::vec3 direction = glm::vec3(0.0f), glm::vec3 position = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float constant = 1.0f, float linear = 0.2f, float quadratic = 0.0f);
	std::shared_ptr<BaseLight> clone() const override;

	lightType getType() const override;


	void update() override;
	void setCamera(Camera* camera);
	
	glm::vec3 direction;
	float angle;

private:
	Camera* camera = nullptr;
};

