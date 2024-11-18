#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Material.h"


class DrawableObject
{
public:
	DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram);
	DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material);
	~DrawableObject();

	void addTransformation(std::unique_ptr<Transformation> transformation, bool continuous = false);
	void render();

private:
	bool firstRender = true;
	std::shared_ptr<Model> model;
	std::shared_ptr<ShaderProgram> shaderProgram;
	
	TransformationComposite transformationComposite;
	
	Material material;
};
