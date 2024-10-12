#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Scene.h"

class Application {
public:
	Application();
	~Application();

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);


	void initialization(int w_width = 800, int w_height = 600, const char* w_name = "Window", GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);
	void createShaders();
	void createModels();
	void createScenes();
	void run();

private:
	GLFWwindow* window;
	ShaderManager shaderManager;
	ModelManager modelManager;

	std::vector<std::shared_ptr<Scene>> Scenes;
};
