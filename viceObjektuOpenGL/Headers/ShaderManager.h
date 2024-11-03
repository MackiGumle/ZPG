#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <GL/glew.h>
#include "ShaderProgram.h"


class ShaderManager {
public:
    void loadShader(const std::string& path, int type, const std::string& name);
    void loadShaderProgram(const std::string& vertexShader, const std::string& fragmentShader, const std::string& name);
    std::shared_ptr<Shader> getShader(const std::string& name) const;
    std::shared_ptr<ShaderProgram> getShaderProgram(const std::string& name) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> shaderPrograms;
};