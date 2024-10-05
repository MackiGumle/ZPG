#include "ShaderManager.h"

ShaderManager::ShaderManager() {

}

ShaderManager::~ShaderManager() {
	for(auto& shader : m_shaderPrograms) {
		glDeleteProgram(shader.second);
	}

}

std::string ShaderManager::readShaderFile(const std::string& path) const {
	std::ifstream file(path);

	if(!file.is_open()) {
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

bool ShaderManager::loadShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name) {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderString= readShaderFile(vertexPath);
	const char* vertexShaderCstr = vertexShaderString.c_str();

	std::string fragmentShaderString = readShaderFile(fragmentPath);
	const char* fragmentShaderCstr = fragmentShaderString.c_str();

	if ((strcmp(vertexShaderCstr, "") == 0) || (strcmp(fragmentShaderCstr, "") == 0))
		return false;

	glShaderSource(vertexShader, 1, &vertexShaderCstr, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderCstr, NULL);

	GLint status;
	char infoLog[512];
	// check for errors in vertex shader
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "[x] ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
		throw std::runtime_error("Shader compilation failed\n\n");
	}

	glCompileShader(fragmentShader);
	// check for errors in fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "[x] ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
		throw std::runtime_error("Shader compilation failed\n\n");
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "[x] ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
		throw std::runtime_error("Shader linking failed\n\n");
	}

	m_shaderPrograms[name] = shaderProgram;
	return true;
}

void ShaderManager::useShaderProgram(const std::string& name) {

	if(m_shaderPrograms.find(name) == m_shaderPrograms.end()) {
		std::cerr << "[x] Shader program not found: " << name << std::endl;
		throw std::runtime_error("Shader program not found");
	}

	glUseProgram(m_shaderPrograms[name]);
}