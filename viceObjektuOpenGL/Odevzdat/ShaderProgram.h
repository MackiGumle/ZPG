#pragma once
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include "ObserverPattern.h"
#include "ShaderLoader.h"
#include "Camera.h"
//#include "Lights.h"

class PointLight;
class ShaderProgram : public Observer, public ShaderLoader
{
public:
	ShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	~ShaderProgram();

	void update() override;
	void setCamera(Camera* camera);

	bool hasUniform(const std::string& name) const;
	//void applyVertexUniform(const std::string& name, const glm::mat4 matrix) const;
	
	template<typename T>
	void applyUniform(const std::string& name, const T& value) const;
	//void applyUniform(const std::string& name, const int& value) const;

	//void addPointLight(std::shared_ptr<PointLight> pointLight);
	
	std::string getVertexPath() const;
	std::string getFragmentPath() const;

	void use() const;

private:
	//GLuint programId;
	std::weak_ptr<Shader> vertexShader;
	std::weak_ptr<Shader> fragmentShader;

	std::string vertexPath;
	std::string fragmentPath;

	Camera* camera = nullptr;
	//std::vector<std::weak_ptr<PointLight>> pointLights;

	template<class U> struct always_false : std::false_type {};


	void linkShaders();
};

