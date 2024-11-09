#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Scene.h"
#include "ObserverPattern.h"
#include <list>
#include <random>
#include <unordered_map>


class Application : IApplicationSubject {
public:
	Application();
	~Application();

	// Callbacks
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
	void key_input(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_input(float xoffset, float yoffset);


	void addObserver(IApplicationObserver* observer);
	void removeObserver(IApplicationObserver* observer);
	void notifyObservers();

	void initialization(int w_width = 800, int w_height = 600, const char* w_name = "Window", GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);
	void createShaders();
	void createModels();
	void createScenes();
	void run();

private:
	GLFWwindow* window;
	ShaderManager shaderManager;
	ModelManager modelManager;

	size_t currentScene = 0;
	std::vector<std::shared_ptr<Scene>> Scenes;
	std::list<IApplicationObserver*> observers;

	// keys being pressed
	std::unordered_map<int, bool> keys;

	// mouse movement
	float lastX;
	float lastY;
};
