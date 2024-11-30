#include "TextureManager.h"
#include <SOIL.h>
#include <iostream>
#include "Texture.h"

void TextureManager::loadTexture(const char* path, std::string name, bool isCubemap)
{
	glActiveTexture(GL_TEXTURE0 + textures.size());

	if (!isCubemap)
	{
		GLuint image = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
		if (!image) {
			std::cout << "[x] An error occurred while loading image:\t" << path << "\tinto:\tGL_TEXTURE" << textures.size();
			exit(EXIT_FAILURE);
		}

		if (textures.find(name) == textures.end())
		{
			textures[name] = std::make_shared<Texture>(path, textures.size(), isCubemap);
		}
		else
		{
			std::cout << "[x] Texture with name:\t" << name << "\talready exists." << std::endl;
			exit(EXIT_FAILURE);
		}

		glBindTexture(GL_TEXTURE_2D, image);
	}
	else
	{
		std::string targetPath(path);

		std::string posxPath = targetPath + "posx.jpg";
		std::string negxPath = targetPath + "negx.jpg";
		std::string posyPath = targetPath + "posy.jpg";
		std::string negyPath = targetPath + "negy.jpg";
		std::string poszPath = targetPath + "posz.jpg";
		std::string negzPath = targetPath + "negz.jpg";

		GLuint image = SOIL_load_OGL_cubemap(
			posxPath.c_str(),
			negxPath.c_str(),
			posyPath.c_str(),
			negyPath.c_str(),
			poszPath.c_str(),
			negzPath.c_str(),
			SOIL_LOAD_RGB,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS
		);

		//GLuint image = SOIL_load_OGL_cubemap("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		if (image == NULL) {
			std::cout << "An error occurred while loading CubeMap.\t" << path << std::endl;
			exit(EXIT_FAILURE);
		}

		if (textures.find(name) == textures.end())
		{
			textures[name] = std::make_shared<Texture>(path, textures.size(), isCubemap);
		}
		else
		{
			std::cout << "[x] Texture with name:\t" << name << "\talready exists." << std::endl;
			exit(EXIT_FAILURE);
		}

		glBindTexture(GL_TEXTURE_2D, image);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, image);
	}
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