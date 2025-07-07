// Author: SIS0049 - Oliver Siskan
#include "Material.h"

Material::Material(float ambient, float diffuse, float specular, float shininess, glm::vec3 color)

	: ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), color(color)
{
}