// Author: SIS0049 - Oliver Siskan
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>
#include <functional>

class Transformation
{
public:
	//bool continous = false;
	virtual glm::mat4 apply() = 0;
};

class Scale : public Transformation
{
public:
	Scale(glm::vec3 vector);
	Scale(float scale);
	glm::mat4 apply() override;

protected:
	glm::vec3 vector;
};

class DynamicScale : public Transformation
{
public:
	DynamicScale(std::function<glm::vec3()> scaleFunc);
	glm::mat4 apply() override;

protected:
	std::function<glm::vec3()> scaleFunc;
};

class Rotation : public Transformation
{
public:
	Rotation(float degrees, glm::vec3 axis);
	glm::mat4 apply() override;

protected:
	float angle;
	glm::vec3 axis;
};

class DynamicRotation : public Transformation
{
public:
	DynamicRotation(std::function<float()> angleFunc, std::function<glm::vec3()> axisFunc);
	glm::mat4 apply() override;

protected:
	std::function<float()> angleFunc;
	std::function<glm::vec3()> axisFunc;
};

class Translation : public Transformation
{
public:
	Translation(glm::vec3 vector);
	glm::mat4 apply() override;

protected:
	glm::vec3 vector;
};

class DynamicTranslation : public Transformation
{
public:
	DynamicTranslation(std::function<glm::vec3()> translationFunc);
	glm::mat4 apply() override;

protected:
	std::function<glm::vec3()> translationFunc;
};

class TransformationComposite : public Transformation
{
public:
	TransformationComposite();
	void addTransformation(std::unique_ptr<Transformation> transformation);
	void clear();
	void clearTranslation();
	glm::mat4 apply() override;

protected:
	std::vector<std::unique_ptr<Transformation>> transformations;
};