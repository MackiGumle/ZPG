// Author: SIS0049 - Oliver Siskan
#pragma once
#include <glm/glm.hpp>

class Material
{
public:
	Material(float ambient = 0.1f, float diffuse = 1.0f, float specular = 0.5f, float shininess = 32.0f, glm::vec3 color = glm::vec3(1.0f));
	float ambient;
	float diffuse;
	float specular;
	float shininess;
	glm::vec3 color;
};