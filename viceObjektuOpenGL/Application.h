#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderManager.h"
#include "ModelManager.h"

class Application {
public:
    Application();
    ~Application();

    void initialization();
    void createShaders();
    void createModels();
    void run();

private:
    GLFWwindow* m_window;
    ShaderManager* m_shaderManager;
    ModelManager* m_modelManager;
};

Application::Application()
{
}

Application::~Application()
{
}