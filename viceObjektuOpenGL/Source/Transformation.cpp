#include "Transformation.h"

Transformation::Transformation()
{
	matrix = glm::mat4(1.0f);
}

glm::mat4 Transformation::getMatrix() const
{
	return matrix;
}

void Transformation::translate(glm::vec3 vector)
{
	matrix = glm::translate(matrix, vector);
}

void Transformation::rotate(float angle, glm::vec3 axis)
{
	matrix = glm::rotate(matrix, glm::radians(angle), axis);
}

void Transformation::scale(glm::vec3 vector)
{
	matrix = glm::scale(matrix, vector);
}

void Transformation::scale(float scalar)
{
	matrix = glm::scale(matrix, glm::vec3(scalar));
}