#pragma once
#include <GL/glew.h>
#include <string>

class Texture
{
public:
	Texture(const char* path = nullptr, GLuint textureUnitIndex = -1, bool isCubemap = false);
	virtual ~Texture() = default;

	std::string getPath() const;
	GLuint getTextureUnitIndex() const;

	void setTextureUnitIndex(GLuint textureUnitIndex);
	void setPath(const std::string& path);

protected:
	GLuint textureUnitIndex;
	std::string path;
	bool isCubemap = false;
};

