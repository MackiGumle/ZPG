#include "Scene.h"


Scene::Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms, std::vector<std::shared_ptr<DrawableObject>> drawableObjects)
	: shaderPrograms(shaderPrograms), drawableObjects(drawableObjects)
{
	for (auto& shaderProgram : this->shaderPrograms)
	{
		camera.addObserver(shaderProgram.get());
	}
}

Scene::Scene(std::vector<std::shared_ptr<ShaderProgram>>&& shaderPrograms, std::vector<std::shared_ptr<DrawableObject>>&& drawableObjects)
	: shaderPrograms(std::move(shaderPrograms)), drawableObjects(std::move(drawableObjects))
{
	for (auto& shaderProgram : this->shaderPrograms)
	{
		camera.addObserver(shaderProgram.get());
	}
}

void Scene::moveCamera(int direction) {
	camera.move(direction);
}

void Scene::rotateCamera(float xoffset, float yoffset) {
	camera.rotate(xoffset, yoffset, true);
}

void Scene::update(std::unordered_map<int, bool>& keys)
{
	camera.update(keys);
}

void Scene::render()
{
	for (auto& drawableObject : drawableObjects)
	{
		drawableObject->rotate(0.5f, glm::vec3(0, 1, 0));
		camera.notifyObservers();
		drawableObject->render();
	}
}