#pragma once
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include "ObserverPattern.h"
#include "ShaderLoader.h"

class ShaderProgram : public ICameraObserver, public ShaderLoader
{
public:
	ShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	~ShaderProgram();

	void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) override;
	void update(glm::mat4 modelMatrix) override;

	void applyVertexUniform(const std::string& name, const glm::mat4 matrix) const;
	void use() const;

private:
	//GLuint programId;
	std::weak_ptr<Shader> vertexShader;
	std::weak_ptr<Shader> fragmentShader;

	void linkShaders();
};

