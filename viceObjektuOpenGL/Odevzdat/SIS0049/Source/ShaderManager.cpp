// Author: SIS0049 - Oliver Siskan
#include "ShaderManager.h"
#include "ShaderProgram.h"
#include "Shader.h"

//ShaderManager::ShaderManager() {
//
//}
//
//ShaderManager::~ShaderManager() {
//
//}

void ShaderManager::loadShader(const std::string& path, int type, const std::string& name)
{
	if (shaders.find(path) != shaders.end())
	{
		std::cerr << "[x] Shader already loaded: " << path << std::endl;
		throw std::runtime_error("Shader already loaded");
	}

	shaders[name] = std::make_shared<Shader>(path, type, name);
}

void ShaderManager::loadShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, const std::string& name)
{
	if (shaderPrograms.find(name) != shaderPrograms.end())
	{
		std::cerr << "[x] Shader program already loaded: " << name << std::endl;
		throw std::runtime_error("Shader program already loaded");
	}

	shaderPrograms[name] = std::make_shared<ShaderProgram>(vertexShader.c_str(), fragmentShader.c_str());

}

std::shared_ptr<Shader> ShaderManager::getShader(const std::string& name) const
{
	if (shaders.find(name) == shaders.end())
	{
		std::cerr << "[x] Shader not found: " << name << std::endl;
		throw std::runtime_error("Shader not found");
	}

	return shaders.at(name);
}

std::shared_ptr<ShaderProgram> ShaderManager::getShaderProgram(const std::string& name) const
{
	if (shaderPrograms.find(name) == shaderPrograms.end())
	{
		std::cerr << "[x] Shader program not found: " << name << std::endl;
		throw std::runtime_error("Shader program not found");
	}

	return shaderPrograms.at(name);
}

