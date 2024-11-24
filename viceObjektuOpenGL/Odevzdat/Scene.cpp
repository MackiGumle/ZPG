#include "Scene.h"
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Lights.h"


Scene::Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms, std::vector<std::shared_ptr<DrawableObject>> drawableObjects)
	: shaderPrograms(shaderPrograms), drawableObjects(drawableObjects)
{
	// Camera flashlight
	auto flashlight = std::make_shared<SpotLight>(15.0f, camera.getFront(), camera.getPosition(), glm::vec3(1), 0.5f);
	this->lights.push_back(flashlight);
	camera.addObserver(flashlight.get());
	flashlight->setCamera(&camera);
	

	for (auto& shaderProgram : this->shaderPrograms)
	{
		camera.addObserver(shaderProgram.get());
		shaderProgram->setCamera(&camera);

		if (shaderProgram->hasUniform("numLights"))
			shaderProgram->applyUniform("numLights", static_cast<int>(this->lights.size()));
	}

	camera.updateCameraVectors();
}

Scene::Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms, std::vector<std::shared_ptr<DrawableObject>> drawableObjects, std::vector<std::shared_ptr<BaseLight>> lights)
	: shaderPrograms(shaderPrograms), drawableObjects(drawableObjects)
{
	// Camera flashlight
	auto flashlight = std::make_shared<SpotLight>(15.0f, camera.getFront(), camera.getPosition(), glm::vec3(1), 0.5f);
	this->lights.push_back(flashlight);
	camera.addObserver(flashlight.get());
	flashlight->setCamera(&camera);

	// Create new instances of lights based on the input
	for (const auto& light : lights)
	{
		//this->lights.push_back(light->clone());
		this->lights.push_back(light);
	}

	// Add observers to camera
	for (auto& shaderProgram : this->shaderPrograms)
	{
		camera.addObserver(shaderProgram.get());
		shaderProgram->setCamera(&camera);

		if (shaderProgram->hasUniform("numLights"))
			shaderProgram->applyUniform("numLights", static_cast<int>(this->lights.size()));
	}

	camera.updateCameraVectors();
}

void Scene::addDrawableObject(std::shared_ptr<DrawableObject> drawableObject)
{
	drawableObjects.push_back(drawableObject);
}

Camera* Scene::getCamera() {
	return &camera;
}

void Scene::rotateCamera(float xoffset, float yoffset) {
	camera.rotate(xoffset, yoffset, true);
}

void Scene::render()
{
	// Apply lights
	for (auto& shaderProgram : shaderPrograms)
	{
		shaderProgram->use();
		if (shaderProgram->hasUniform("numLights"))
		{
			auto i = 0;
			for (auto& light : lights)
			{
				auto name = "lights[" + std::to_string(i) + "]";
				
				auto type = light->getType();
				switch (type)
				{
				case POINT_LIGHT:
					shaderProgram->applyUniform(name, *std::dynamic_pointer_cast<PointLight>(light));
					break;
				case DIRECTIONAL_LIGHT:
					shaderProgram->applyUniform(name, *std::dynamic_pointer_cast<DirectionalLight>(light));
					break;
				case SPOT_LIGHT:
					shaderProgram->applyUniform(name, *std::dynamic_pointer_cast<SpotLight>(light));
					break;

				default:
					throw std::runtime_error("Unknown light type");
					break;
				}

				//shaderProgram->applyUniform(name, *light.get());
				++i;
			}

			//shaderProgram->applyUniform("lights[" + std::to_string(i) + "]", camera.getSpotLight());
		}
	}

	for (auto& drawableObject : drawableObjects)
	{

		//camera.notifyObservers();

		drawableObject->render();
	}
}
