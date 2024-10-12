#include "DrawableObject.h"

DrawableObject::DrawableObject(const Model& model, const ShaderProgram& shaderProgram)
	: model(model), shaderProgram(shaderProgram)
{
}

DrawableObject::~DrawableObject()
{
}

void DrawableObject::render()
{
	shaderProgram.use();
	model.render();
}

void DrawableObject::scale(glm::vec3 vector)
{
	transformation.scale(vector);
}

void DrawableObject::rotate(float angle, glm::vec3 axis)
{
	transformation.rotate(angle, axis);
}

void DrawableObject::translate(glm::vec3 vector)
{
	transformation.translate(vector);
}