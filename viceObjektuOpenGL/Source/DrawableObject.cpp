#include "DrawableObject.h"

DrawableObject::DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram)
	: model(model), shaderProgram(shaderProgram), modelMatrix(glm::mat4(1.0f))
{
}

DrawableObject::~DrawableObject()
{
}

void DrawableObject::addTransformation(std::unique_ptr<Transformation> transformation, bool continuous)
{
	//transformations.push_back(std::make_unique<Transformation>(transformation));
	
	if (continuous) {
		continuousTransformations.push_back(std::move(transformation));
	}
	else {
		transformations.push_back(std::move(transformation));
	}
}

void DrawableObject::render()
{
	if (firstRender)
	{
		for (auto& transformation : transformations)
		{
			transformation->set(modelMatrix);
		}
		firstRender = false;
	}

	//glm::mat4 tempModelMatrix = modelMatrix;

	for (auto& transformation : continuousTransformations)
	{
		transformation->set(modelMatrix);
	}

	shaderProgram.lock()->use();
	shaderProgram.lock()->applyVertexUniform("modelMatrix", modelMatrix);
	model.lock()->render();
}
