#include "Transformation.h"


Scale::Scale(glm::vec3 vector) : vector(vector)
{
}

Scale::Scale(float scale) : vector(glm::vec3(scale))
{
}

glm::mat4 Scale::apply()
{
	return glm::scale(glm::mat4(1.0f), vector);
}

DynamicScale::DynamicScale(std::function<glm::vec3()> scaleFunc) : scaleFunc(scaleFunc)
{
}

glm::mat4 DynamicScale::apply()
{
	return glm::scale(glm::mat4(1.0f), scaleFunc());
}

Rotation::Rotation(float degrees, glm::vec3 axis) : angle(degrees), axis(axis)
{
}

glm::mat4 Rotation::apply()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
}

DynamicRotation::DynamicRotation(std::function<float()> angleFunc, std::function<glm::vec3()> axisFunc) : angleFunc(angleFunc), axisFunc(axisFunc)
{

}

glm::mat4 DynamicRotation::apply()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(angleFunc()), axisFunc());
}

Translation::Translation(glm::vec3 vector) : vector(vector)
{
}

glm::mat4 Translation::apply()
{
	return glm::translate(glm::mat4(1.0f), vector);
}

DynamicTranslation::DynamicTranslation(std::function<glm::vec3()> translationFunc) : translationFunc(translationFunc)
{
}

glm::mat4 DynamicTranslation::apply()
{
	return glm::translate(glm::mat4(1.0f), translationFunc());
}

TransformationComposite::TransformationComposite()
{
}

void TransformationComposite::addTransformation(std::unique_ptr<Transformation> transformation)
{
	transformations.push_back(std::move(transformation));
}

void TransformationComposite::clear()
{
	transformations.clear();
}

void TransformationComposite::clearTranslation()
{
	transformations.erase(
		std::remove_if(
			transformations.begin(),
			transformations.end(),
			[](const std::unique_ptr<Transformation>& transformation) {
				return dynamic_cast<Translation*>(transformation.get()) != nullptr;
			}
		),
		transformations.end()
	);
}

glm::mat4 TransformationComposite::apply()
{
	glm::mat4 result = glm::mat4(1.0f);
	for (auto& transformation : transformations)
	{
		result = transformation->apply() * result;
	}
	return result;
}