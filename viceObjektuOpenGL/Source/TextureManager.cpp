#include "TextureManager.h"
#include <SOIL.h>
#include <iostream>
#include "Texture.h"

void TextureManager::loadTexture(const char* path, std::string name)
{
	glActiveTexture(GL_TEXTURE0 + textures.size());

	GLuint image = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	if (!image) {
		std::cout << "[x] An error occurred while loading image:\t" << path << "\tinto:\tGL_TEXTURE" << textures.size();
		exit(EXIT_FAILURE);
	}

	if (textures.find(name) == textures.end())
	{
		textures[name] = std::make_shared<Texture>(path, textures.size());
	}
	else
	{
		std::cout << "[x] Texture with name:\t" << name << "\talready exists." << std::endl;
		exit(EXIT_FAILURE);
	}

	glBindTexture(GL_TEXTURE_2D, image);
}

std::shared_ptr<Texture> TextureManager::getTexture(const std::string& name) const
{
	if (textures.find(name) != textures.end())
	{
		return textures.at(name);
	}
	else
	{
		std::cout << "[x] Texture with name:\t" << name << "\tdoes not exist." << std::endl;
		exit(EXIT_FAILURE);
	}
}