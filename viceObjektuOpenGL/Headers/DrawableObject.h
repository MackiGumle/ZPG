#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

// Inherits from Transformable, .rotate(), .translate(), .scale() methods available
class DrawableObject
{
public:
	DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram);
	~DrawableObject();

	void addTransformation(std::unique_ptr<Transformation> transformation, bool continuous = false);
	void render();

private:
	bool firstRender = true;
	std::weak_ptr<Model> model;
	std::weak_ptr<ShaderProgram> shaderProgram;
	
	TransformationComposite transformationComposite;
	
	//glm::mat4 modelMatrix; // final transformation matrix
	//std::vector<std::unique_ptr<Transformation>> transformations;
	//std::vector<std::unique_ptr<Transformation>> continuousTransformations;
};
