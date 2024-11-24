#include "DrawableObject.h"

DrawableObject::DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram)
	: model(model), shaderProgram(shaderProgram)
{
}

DrawableObject::DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material)
	: model(model), shaderProgram(shaderProgram), material(material)
{
}

DrawableObject::~DrawableObject()
{
}

void DrawableObject::addTransformation(std::unique_ptr<Transformation> transformation, bool continuous)
{
	transformationComposite.addTransformation(std::move(transformation));
}

void DrawableObject::render()
{
	auto modelMatrix = transformationComposite.apply();

	shaderProgram->applyUniform("modelMatrix", modelMatrix);

	if (shaderProgram->hasUniform("material.color"))
	{
		shaderProgram->applyUniform("material", material);
	}

	shaderProgram->use();
	model->render();
	glUseProgram(0);
}
