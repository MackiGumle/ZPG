#include "Scene.h"


Scene::Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms, std::vector<std::shared_ptr<DrawableObject>> drawableObjects)
	: shaderPrograms(shaderPrograms), drawableObjects(drawableObjects)
{
}

Scene::Scene(std::vector<std::shared_ptr<ShaderProgram>>&& shaderPrograms, std::vector<std::shared_ptr<DrawableObject>>&& drawableObjects)
	: shaderPrograms(std::move(shaderPrograms)), drawableObjects(std::move(drawableObjects))
{
}

//
//void Scene::addModel(std::shared_ptr<Model> model)
//{
//	if (models.find(model->getName()) != models.end())
//	{
//		models[model->getName()] = model;
//	}
//}
//
//void Scene::addShader(std::shared_ptr<Shader> shader)
//{
//	if (shaders.find(shader->getName()) != shaders.end())
//	{
//		shaders[shader->getName()] = shader;
//	}
//}
//
//void Scene::addShaderProgram(std::string vertexShaderName, std::string fragmentShaderName, std::string name)
//{
//	if (shaders.find(vertexShaderName) == shaders.end())
//	{
//		std::cout << "[x] Vertex shader with name " + vertexShaderName + " not found\n";
//		throw std::runtime_error("Vertex shader with name " + vertexShaderName + " not found");
//	}
//
//	if (shaders.find(fragmentShaderName) == shaders.end())
//	{
//		std::cout << "[x] Fragment shader with name " + fragmentShaderName + " not found\n";
//		throw std::runtime_error("Fragment shader with name " + fragmentShaderName + " not found");
//	}
//
//	if (shaderPrograms.find(name) != shaderPrograms.end())
//	{
//		std::cout << "[x] ShaderProgram " << name << " already exists\n";
//		throw std::runtime_error("ShaderProgram " + name + " already exists");
//	}
//
//	shaderPrograms[name] = std::make_shared<ShaderProgram>(shaders.at(vertexShaderName), shaders.at(fragmentShaderName));
//}
//
//void Scene::addDrawableObject(std::string modelName, std::string shaderProgramName)
//{
//	if (models.find(modelName) == models.end())
//	{
//		std::cout << "[x] Model with name " + modelName + " not found\n";
//		throw std::runtime_error("Model with name " + modelName + " not found");
//	}
//
//	if (shaderPrograms.find(shaderProgramName) == shaderPrograms.end())
//	{
//		std::cout << "[x] Shader with name " + shaderProgramName + " not found\n";
//		throw std::runtime_error("Shader with name " + shaderProgramName + " not found");
//	}
//
//	drawableObjects.push_back(std::make_unique<DrawableObject>(models.at(modelName), shaderPrograms.at(shaderProgramName)));
//}

void Scene::render()
{
	for (auto& drawableObject : drawableObjects)
	{
		drawableObject->render();
	}
}