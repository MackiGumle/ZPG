#pragma once
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
	~ShaderProgram();
	void applyVertexUniform(const std::string& name, const glm::mat4& matrix) const;
	void use() const;

private:
	GLuint programId;
	const Shader& vertexShader;
	const Shader& fragmentShader;

	void linkShaders();
};

