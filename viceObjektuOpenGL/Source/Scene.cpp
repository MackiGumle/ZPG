#include "Scene.h"


Scene::Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms, std::vector<std::shared_ptr<DrawableObject>> drawableObjects)
	: shaderPrograms(shaderPrograms), drawableObjects(drawableObjects)
{
}

Scene::Scene(std::vector<std::shared_ptr<ShaderProgram>>&& shaderPrograms, std::vector<std::shared_ptr<DrawableObject>>&& drawableObjects)
	: shaderPrograms(std::move(shaderPrograms)), drawableObjects(std::move(drawableObjects))
{
}

void Scene::render()
{
	for (auto& drawableObject : drawableObjects)
	{
		drawableObject->render();
	}
}