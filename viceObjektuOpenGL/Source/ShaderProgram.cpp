#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader)
	: vertexShader(vertexShader), fragmentShader(fragmentShader)
{
	programId = glCreateProgram();
	std::cout << "[i] Shader program created: " << programId << '\n';

	linkShaders();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programId);
	std::cout << "[i] Shader program deleted: " << programId << '\n';
}

void ShaderProgram::applyVertexUniform(const std::string& name, const glm::mat4& matrix) const
{
	GLint location = glGetUniformLocation(programId, name.c_str());
	if(location == -1)
	{
		std::cout << "[x] ERROR::SHADER::UNIFORM::NOT_FOUND\t" << name + '\t' << vertexShader.getPath() + '\n';
		throw std::runtime_error("Uniform not found: " + vertexShader.getPath());
	}

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::use() const
{
	glUseProgram(programId);
}

void ShaderProgram::linkShaders()
{
	vertexShader.attachToProgram(programId);
	fragmentShader.attachToProgram(programId);
	glLinkProgram(programId);

	GLint status;
	char infoLog[512];
	glGetProgramiv(programId, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		std::cout << "[x] ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
		throw std::runtime_error("Shader linking failed\n\n");
	}

	std::cout << "[i] Shader program linked: " << programId << ' ' << vertexShader.getPath() + " + " + fragmentShader.getPath() << '\n';
}