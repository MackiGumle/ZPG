#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>


class Shader
{
public:
	Shader() = default;
	Shader(const std::string path, int type, std::string name);
	~Shader();
	std::string getPath() const;
	std::string getName() const;
	void attachToProgram(GLuint programId) const;

private:
	GLuint shaderId;
	std::string path;
	std::string name;

	std::string readShaderFile(const std::string& path) const;
	void loadShader(const std::string path, int type);
	GLuint compileShader(const std::string& shaderSource, GLenum shaderType) const;
};

