#include "ShaderManager.h"

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

std::shared_ptr<Shader> ShaderManager::getShader(const std::string& name) const
{
	if (shaders.find(name) == shaders.end())
	{
		std::cerr << "[x] Shader not found: " << name << std::endl;
		throw std::runtime_error("Shader not found");
	}

	return shaders.at(name);
}
