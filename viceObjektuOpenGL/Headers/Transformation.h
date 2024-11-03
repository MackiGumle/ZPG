#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Transformation
{
public:
	//Transformation();
	bool continous = false;
	virtual void set(glm::mat4& matrix) = 0;
};

class Scale : public Transformation
{
public:
	Scale(glm::vec3 vector);
	Scale(float scale);
	void set(glm::mat4& matrix) override;

private:
	glm::vec3 vector;
};

class Rotation : public Transformation
{
public:
	Rotation(float degrees, glm::vec3 axis);
	void set(glm::mat4& matrix) override;

private:
	float angle;
	glm::vec3 axis;
};

class Translation : public Transformation
{
public:
	Translation(glm::vec3 vector);
	void set(glm::mat4& matrix) override;

private:
	glm::vec3 vector;
};
