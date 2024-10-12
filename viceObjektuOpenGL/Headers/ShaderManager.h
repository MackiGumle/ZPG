#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <GL/glew.h>
#include "ShaderProgram.h"


class ShaderManager {
public:
    //ShaderManager();
    //~ShaderManager();

    //std::string readShaderFile(const std::string& path) const;
  /*  bool loadShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name);
    void useShaderProgram(const std::string& name);*/
    void loadShader(const std::string& path, int type, const std::string& name);
    std::shared_ptr<Shader> getShader(const std::string& name) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
};