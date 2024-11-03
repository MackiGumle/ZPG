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
	vertexPath = vertexFile;
	fragmentPath = fragmentFile;
}

ShaderProgram::~ShaderProgram()
{
	//glDeleteProgram(shaderProgramID);
	deleteShader();
	std::cout << "[i] Shader program deleted: " << shaderProgramID << '\n';
}

void ShaderProgram::update()
{
	//use();

	applyVertexUniform("viewMatrix", camera->getViewMatrix());
	applyVertexUniform("projectionMatrix", camera->getProjectionMatrix());

	if (hasVertexUniform("viewPos"))
	{
		applyVertexUniform("viewPos", camera->getPosition());
	}
}

void ShaderProgram::setCamera(Camera* camera)
{
	this->camera = camera;
}

bool ShaderProgram::hasVertexUniform(const std::string& name) const
{
	GLint location = glGetUniformLocation(shaderProgramID, name.c_str());
	return location != -1;
}

//void ShaderProgram::applyVertexUniform(const std::string& name, const glm::mat4 matrix) const
//{
//	GLint location = glGetUniformLocation(shaderProgramID, name.c_str());
//	if(location == -1)
//	{
//		std::cout << "[x] ERROR::SHADER::UNIFORM::NOT_FOUND\t" << name + '\t' << vertexShader.lock()->getPath() + '\n';
//		throw std::runtime_error("Uniform not found: " + vertexShader.lock()->getPath());
//	}
//
//	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
//}

template<typename T>
void ShaderProgram::applyVertexUniform(const std::string& name, const T& value) const
{
	GLint location = glGetUniformLocation(shaderProgramID, name.c_str());
	if (location == -1)
	{
		std::cout << "[x] ERROR::SHADER::UNIFORM::NOT_FOUND\t'" << name << "'\t" << getVertexPath();
		throw std::runtime_error("Uniform not found: " + getVertexPath());
	}

	if constexpr (std::is_same_v<T, glm::mat4>)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
	else if constexpr (std::is_same_v<T, glm::mat3>)
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
	else if constexpr (std::is_same_v<T, glm::vec3>)
	{
		glUniform3fv(location, 1, glm::value_ptr(value));
	}
	else if constexpr (std::is_same_v<T, glm::vec4>)
	{
		glUniform4fv(location, 1, glm::value_ptr(value));
	}
	else if constexpr (std::is_same_v<T, float>)
	{
		glUniform1f(location, value);
	}
	else if constexpr (std::is_same_v<T, int>)
	{
		glUniform1i(location, value);
	}
	else
	{
		static_assert(always_false<T>::value, "Unsupported uniform type");
	}
}

std::string ShaderProgram::getVertexPath() const
{
	return vertexPath;
}

std::string ShaderProgram::getFragmentPath() const
{
	return fragmentPath;
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