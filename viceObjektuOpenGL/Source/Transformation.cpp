#include "Transformation.h"


Scale::Scale(glm::vec3 vector) : vector(vector)
{
}

Scale::Scale(float scale) : vector(glm::vec3(scale))
{
}

void Scale::apply(glm::mat4& matrix)
{
	matrix = glm::scale(matrix, vector);
}

Rotation::Rotation(float degrees, glm::vec3 axis) : angle(degrees), axis(axis)
{
}

void Rotation::apply(glm::mat4& matrix)
{
	matrix = glm::rotate(matrix, glm::radians(angle), axis);
}

Translation::Translation(glm::vec3 vector) : vector(vector)
{
}

void Translation::apply(glm::mat4& matrix)
{
	matrix = glm::translate(matrix, vector);
}
