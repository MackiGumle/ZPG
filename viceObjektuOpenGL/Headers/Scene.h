#pragma once
#include <unordered_map>
#include <vector>

#include "DrawableObject.h"
#include "ShaderProgram.h"

class Scene
{
public:
	Scene(std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms, std::vector<std::shared_ptr<DrawableObject>> drawableObjects);
	Scene(std::vector<std::shared_ptr<ShaderProgram>>&& shaderPrograms, std::vector<std::shared_ptr<DrawableObject>>&& drawableObjects);
	/*void addModel(std::shared_ptr<Model> model);
	void addShader(std::shared_ptr<Shader> shader);*/
	void addShaderProgram(std::string vertexShaderName, std::string fragmentShaderName, std::string name);
	void addDrawableObject(std::string modelName, std::string shaderProgramName);

	void render();

private:
	// To be removed, Scene should not own models and shaders, instead it should own drawable objects and shader programs
	//std::unordered_map<std::string, std::shared_ptr<Model>> models;
	//std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
	//
	std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms;
	std::vector<std::shared_ptr<DrawableObject>> drawableObjects;
};

