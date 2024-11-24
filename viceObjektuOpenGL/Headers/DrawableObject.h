#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Material.h"
#include "ObserverPattern.h"

// Subject of Light
class DrawableObject : public Subject
{
public:
	DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram);
	DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material);
	~DrawableObject();

	void addTransformation(std::unique_ptr<Transformation> transformation, bool continuous = false);
	void render();

	glm::vec3 getPosition() const { return position; }

private:
	bool firstRender = true;
	std::shared_ptr<Model> model;
	std::shared_ptr<ShaderProgram> shaderProgram;
	
	TransformationComposite transformationComposite;

	glm::vec3 position;
	
	Material material;
};
