#include "Scene.h"


Scene::Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms, std::vector<std::shared_ptr<DrawableObject>> drawableObjects)
	: shaderPrograms(shaderPrograms), drawableObjects(drawableObjects)
{
	for (auto& shaderProgram : this->shaderPrograms)
	{
		camera.addObserver(shaderProgram.get());
		shaderProgram->setCamera(&camera);
	}
}

Scene::Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms, std::vector<std::shared_ptr<DrawableObject>> drawableObjects, std::vector<std::shared_ptr<BaseLight>> lights)
	: shaderPrograms(shaderPrograms), drawableObjects(drawableObjects), lights(lights)
{
	for (auto& shaderProgram : this->shaderPrograms)
	{
		camera.addObserver(shaderProgram.get());
		shaderProgram->setCamera(&camera);

		if (shaderProgram->hasUniform("numLights"))
			// +1 for the camera light
			shaderProgram->applyUniform("numLights", static_cast<int>(lights.size() + 1));
		
	}
}

Scene::Scene(std::vector<std::shared_ptr<ShaderProgram>>&& shaderPrograms, std::vector<std::shared_ptr<DrawableObject>>&& drawableObjects)
	: shaderPrograms(std::move(shaderPrograms)), drawableObjects(std::move(drawableObjects))
{
	for (auto& shaderProgram : this->shaderPrograms)
	{
		camera.addObserver(shaderProgram.get());
		shaderProgram->setCamera(&camera);
	}
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
				shaderProgram->applyUniform(name, *light.get());
				++i;
			}

			shaderProgram->applyUniform("lights[" + std::to_string(i) + "]", camera.getSpotLight());
		}
	}

	for (auto& drawableObject : drawableObjects)
	{

		//camera.notifyObservers();

		drawableObject->render();
	}
}
