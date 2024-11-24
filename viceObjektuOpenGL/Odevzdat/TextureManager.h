#pragma once
#include <GL/glew.h>
#include <vector>
//#include "Texture.h"
#include <memory>
#include <unordered_map>
#include <string>

class Texture;

// Responsible for loading textures and managing them
// Each DrawableObject has a pointer to a Texture
class TextureManager
{
public:
	TextureManager() = default;
	virtual ~TextureManager() = default;

	void loadTexture(const char* path, std::string name);
	std::shared_ptr<Texture> getTexture(const std::string& name) const;

private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
	GLuint currentTexture = GL_TEXTURE0;
};
