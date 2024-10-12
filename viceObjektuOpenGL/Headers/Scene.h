#pragma once
#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"

class Scene
{
public:
	Scene();
	~Scene();

	void addModel(const Model& model);
	void addShader(const Shader& shader);
	void addDrawableObject(const DrawableObject& drawableObject);
	void addShaderProgram(const ShaderProgram& shaderProgram);

	void render();

private:
	std::vector<Model&> models;
	std::vector<Shader&> shaders;
	std::vector<DrawableObject> drawableObjects;
	std::vector<ShaderProgram> shaderPrograms;
};

