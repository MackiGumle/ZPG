#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <GL/glew.h>


class ShaderManager {
public:
    ShaderManager();
    ~ShaderManager();

    std::string readShaderFile(const std::string& path) const;
    bool loadShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name);
    void useShaderProgram(const std::string& name);

private:
    std::unordered_map<std::string, GLuint> m_shaderPrograms;
};