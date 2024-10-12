#include "Transformation.h"

Transformation::Transformation()
{
	matrix = glm::mat4(1.0f);
}

void Transformation::translate(glm::vec3 vector)
{
	matrix = glm::translate(matrix, vector);
}

void Transformation::rotate(float angle, glm::vec3 axis)
{
	matrix = glm::rotate(matrix, angle, axis);
}

void Transformation::scale(glm::vec3 vector)
{
	matrix = glm::scale(matrix, vector);
}