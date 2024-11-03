#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader)
	: vertexShader(vertexShader), fragmentShader(fragmentShader)
{
	shaderProgramID = glCreateProgram();
	std::cout << "[i] Shader program created: " << shaderProgramID << '\n';

	linkShaders();
}

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	loadShader(vertexFile, fragmentFile);
}

ShaderProgram::~ShaderProgram()
{
	//glDeleteProgram(shaderProgramID);
	deleteShader();
	std::cout << "[i] Shader program deleted: " << shaderProgramID << '\n';
}

void ShaderProgram::update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	//use();
	applyVertexUniform("viewMatrix", viewMatrix);
	applyVertexUniform("projectionMatrix", projectionMatrix);
}

void ShaderProgram::update(glm::mat4 modelMatrix)
{
	applyVertexUniform("modelMatrix", modelMatrix);
}

void ShaderProgram::applyVertexUniform(const std::string& name, const glm::mat4 matrix) const
{
	GLint location = glGetUniformLocation(shaderProgramID, name.c_str());
	if(location == -1)
	{
		std::cout << "[x] ERROR::SHADER::UNIFORM::NOT_FOUND\t" << name + '\t' << vertexShader.lock()->getPath() + '\n';
		throw std::runtime_error("Uniform not found: " + vertexShader.lock()->getPath());
	}

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::use() const
{
	glUseProgram(shaderProgramID);
}

void ShaderProgram::linkShaders()
{
	vertexShader.lock()->attachToProgram(shaderProgramID);
	fragmentShader.lock()->attachToProgram(shaderProgramID);
	glLinkProgram(shaderProgramID);

	GLint status;
	char infoLog[512];
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		std::cout << "[x] ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
		throw std::runtime_error("Shader linking failed\n\n");
	}

	std::cout << "[i] Shader program linked: " << shaderProgramID << ' ' << vertexShader.lock()->getPath() + " + " + fragmentShader.lock()->getPath() << '\n';
}