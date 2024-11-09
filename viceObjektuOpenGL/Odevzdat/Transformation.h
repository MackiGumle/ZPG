#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Transformation
{
public:
	Transformation();
	
	glm::mat4 getMatrix() const;
	void translate(glm::vec3 vector);
	void rotate(float angle, glm::vec3 axis);
	void scale(glm::vec3 vector);
	void scale(float scalar);

private:
	glm::mat4 matrix;
};

