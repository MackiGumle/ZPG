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

Scene::Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms, std::vector<std::shared_ptr<DrawableObject>> drawableObjects, std::vector<std::shared_ptr<PointLight>> PointLights)
	: shaderPrograms(shaderPrograms), drawableObjects(drawableObjects), pointLights(PointLights)
{
	for (auto& shaderProgram : this->shaderPrograms)
	{
		camera.addObserver(shaderProgram.get());
		shaderProgram->setCamera(&camera);

		if (shaderProgram->hasVertexUniform("numLights"))
			shaderProgram->applyUniform("numLights", static_cast<int>(pointLights.size()));

		//for (auto& pointLight : pointLights)
		//{
		//	shaderProgram->addPointLight(pointLight);
		//}
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
	for (auto& shaderProgram : shaderPrograms)
	{

	}

	// Apply lights
	for (auto& shaderProgram : shaderPrograms)
	{
		shaderProgram->use();
		if (shaderProgram->hasVertexUniform("numLights"))
		{

			auto i = 0;
			for (auto& pointLight : pointLights)
			{
				auto name = "lights[" + std::to_string(i) + "]";
				shaderProgram->applyUniform(name, *pointLight.get());
				++i;
			}
		}
	}

	for (auto& drawableObject : drawableObjects)
	{

		//camera.notifyObservers();

		drawableObject->render();
	}
}
