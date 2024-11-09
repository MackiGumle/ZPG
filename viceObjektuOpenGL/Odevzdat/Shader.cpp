#include "Shader.h"

Shader::Shader(const std::string path, int type, std::string name): path(path), name(name) {
	shaderId = glCreateShader(type);
	
	loadShader(path, type);
	std::cout << "[i] Shader created: " << path << std::endl;
}

Shader::~Shader() {
	glDeleteShader(shaderId);
	std::cout << "[i] Shader deleted: " << path << std::endl;
}

std::string Shader::getPath() const {
	return path;
}

std::string Shader::getName() const {
	return name;
}

std::string Shader::readShaderFile(const std::string& path) const {
	std::ifstream file(path);

	if (!file.is_open()) {
		std::cerr << "[x] Could not open shader file: " << path << std::endl;
		return "";
	}

	file.seekg(0, std::ios::end);
	size_t fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string fileContents(fileSize, '\0');
	file.read(&fileContents[0], fileSize);

	file.close();

	return fileContents;
}

void Shader::loadShader(const std::string path, int type)
{
	std::string shaderString = readShaderFile(path);
	const char* shaderCstr = shaderString.c_str();

	if (strcmp(shaderCstr, "") == 0)
		throw std::runtime_error("Shader file not found or empty: " + path);

	glShaderSource(shaderId, 1, &shaderCstr, NULL);

	GLint status;
	char infoLog[512];
	// check for errors in vertex shader
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cout << "[x] ERROR::SHADER::COMPILATION_FAILED\t" <<  path << "\n" << infoLog << "\n";
		throw std::runtime_error("Shader compilation failed: " + path);
	}

	std::cout << "[i] Shader compiled: " << path << '\n';
}

void Shader::attachToProgram(GLuint programId) const
{
	glAttachShader(programId, shaderId);
}