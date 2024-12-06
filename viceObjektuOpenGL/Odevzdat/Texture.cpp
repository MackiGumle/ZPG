#include "Texture.h"
#include <iostream>
#include <SOIL.h>
#include "ShaderProgram.h"

Texture::Texture(const char* path, GLuint textureUnitIndex, bool isCubemap) : path(path), textureUnitIndex(textureUnitIndex), isCubemap(isCubemap)
{
	
}

std::string Texture::getPath() const { return path; }
GLuint Texture::getTextureUnitIndex() const { return textureUnitIndex; }

void Texture::setTextureUnitIndex(GLuint textureUnitIndex) { this->textureUnitIndex = textureUnitIndex; }
void Texture::setPath(const std::string& path) { this->path = path; }