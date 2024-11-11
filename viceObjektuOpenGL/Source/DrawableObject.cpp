#include "DrawableObject.h"

DrawableObject::DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram)
	: model(model), shaderProgram(shaderProgram)
{
}

DrawableObject::~DrawableObject()
{
}

void DrawableObject::addTransformation(std::unique_ptr<Transformation> transformation, bool continuous)
{
	//transformations.push_back(std::make_unique<Transformation>(transformation));
	/*
	if (continuous) {
		continuousTransformations.push_back(std::move(transformation));
	}
	else {
		transformations.push_back(std::move(transformation));
	}*/

	transformationComposite.addTransformation(std::move(transformation));
}

void DrawableObject::render()
{
	//if (firstRender)
	//{
	//	for (auto& transformation : transformations)
	//	{
	//		transformation->apply(modelMatrix);
	//	}
	//	firstRender = false;
	//}

	//glm::mat4 tempModelMatrix = modelMatrix;

	//for (auto& transformation : continuousTransformations)
	//{
	//	transformation->apply(modelMatrix);
	//}

	auto modelMatrix = transformationComposite.apply();

	shaderProgram.lock()->use();
	shaderProgram.lock()->applyUniform("modelMatrix", modelMatrix);
	model.lock()->render();
}
