#pragma once
#include <string>
#include <unordered_map>
#include <GL/glew.h>


class ShaderManager {
public:
    //ShaderManager(Application& app);
    ShaderManager();
    ~ShaderManager();

    void loadShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name);

    GLuint getShaderProgram(const std::string& name);

private:
    //Application& m_app;
    std::unordered_map<std::string, GLuint> m_shaderPrograms;
};