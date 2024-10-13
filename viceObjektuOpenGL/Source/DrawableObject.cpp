#include "DrawableObject.h"

DrawableObject::DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram)
	: model(model), shaderProgram(shaderProgram)
{
}

DrawableObject::~DrawableObject()
{
}

void DrawableObject::render()
{
	shaderProgram.lock()->use();
	shaderProgram.lock()->applyVertexUniform("transform", transformation.getMatrix());
	model.lock()->render();
}

void DrawableObject::scale(glm::vec3 vector)
{
	transformation.scale(vector);
}

void DrawableObject::scale(float scalar)
{
	transformation.scale(scalar);
}

void DrawableObject::rotate(float angle, glm::vec3 axis)
{
	transformation.rotate(angle, axis);
}

void DrawableObject::translate(glm::vec3 vector)
{
	transformation.translate(vector);
}