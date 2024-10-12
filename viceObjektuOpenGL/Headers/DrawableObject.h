#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"


class DrawableObject
{
public:
	DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram);
	//DrawableObject(std::shared_ptr<Model>& model, std::shared_ptr<ShaderProgram>& shaderProgram);
	~DrawableObject();

	void render();

	void scale(glm::vec3 vector);
	void rotate(float angle, glm::vec3 axis);
	void translate(glm::vec3 vector);

private:
	std::weak_ptr<Model> model;
	std::weak_ptr<ShaderProgram> shaderProgram;
	Transformation transformation;
};

