#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"


class DrawableObject
{
public:
	DrawableObject(const Model& model, const ShaderProgram& shaderProgram);
	~DrawableObject();

	void render();

	void scale(glm::vec3 vector);
	void rotate(float angle, glm::vec3 axis);
	void translate(glm::vec3 vector);

private:
	const Model& model;
	const ShaderProgram& shaderProgram;
	Transformation transformation;
};

