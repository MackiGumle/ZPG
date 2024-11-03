#include "Application.h"
#include "tree.h"
#include "bushes.h"
#include "sphere.h"
#include "gift.h"
#include "suzi_flat.h"


float Application::deltaTime = 0.0f;

Application::Application() : window(nullptr), shaderManager(ShaderManager()), modelManager(ModelManager()) {

}

Application::~Application() {
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::error_callback(int error, const char* description) { fputs(description, stderr); }

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app) {
		app->key_input(window, key, scancode, action, mods);
	}
}

void Application::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Application::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) {
	static bool firstMouse = true;
	static float lastX = 960.0f, lastY = 540.0f;

	if (firstMouse) {
		lastX = static_cast<float>(x);
		lastY = static_cast<float>(y);
		firstMouse = false;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y;

	lastX = x;
	lastY = y;

	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app) {
		app->mouse_input(xoffset, yoffset);
	}

}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

void Application::key_input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:

		if (keys.find(key) != keys.end())
		{
			keys[key] = true;
			//std::cout << "[i] Key Pressed:\t" << key << "\t" << keys[key] << std::endl;
		}

		switch (key)
		{
		case GLFW_KEY_UP:
			currentScene = (currentScene + 1) % Scenes.size();
			currentCamera = Scenes[currentScene]->getCamera();
			std::cout << "[i] Current Scene: " << currentScene << "\tCamera: " << currentCamera << std::endl;
			break;
		case GLFW_KEY_DOWN:
			currentScene = (currentScene + Scenes.size() - 1) % Scenes.size();
			currentCamera = Scenes[currentScene]->getCamera();
			std::cout << "[i] Current Scene: " << currentScene << "\tCamera: " << currentCamera << std::endl;
			break;
		}
		break;

	case GLFW_RELEASE:
		if (keys.find(key) != keys.end())
		{
			keys[key] = false;
			//std::cout << "[i] Key Released:\t" << key << "\t" << keys[key] << std::endl;
		}
		break;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void Application::mouse_input(float xoffset, float yoffset)
{
	currentCamera->rotate(xoffset, yoffset);
	//Scenes[currentScene]->rotateCamera(xoffset, yoffset);
}

void Application::initialization(int w_width, int w_height, const char* w_name, GLFWmonitor* monitor, GLFWwindow* share)
{
	std::cout << "---\tInitializing GLFW\t---" << std::endl;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(w_width, w_height, w_name, monitor, share);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Sets the key callback
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	/*glfwsetmousebuttoncallback(m_window, button_callback);
	glfwsetwindowfocuscallback(m_window, window_focus_callback);
	glfwsetwindowiconifycallback(m_window, window_iconify_callback);
	glfwSetWindowSizeCallback(m_window, window_size_callback);*/
	glEnable(GL_DEPTH_TEST);

	// Set Keybinds
	keys[GLFW_KEY_W] = false;
	keys[GLFW_KEY_S] = false;
	keys[GLFW_KEY_A] = false;
	keys[GLFW_KEY_D] = false;
	keys[GLFW_KEY_E] = false;
	keys[GLFW_KEY_Q] = false;
	keys[GLFW_KEY_UP] = false;
	keys[GLFW_KEY_DOWN] = false;
	keys[GLFW_KEY_LEFT] = false;
	keys[GLFW_KEY_RIGHT] = false;

	std::cout << "\n\n";
}

void Application::createShaders()
{
	shaderManager.loadShaderProgram("Shaders/vertexShader.vs", "Shaders/ShaderGreen.fs", "SC0_Green");

	shaderManager.loadShaderProgram("Shaders/vertexShader.vs", "Shaders/fragmentShader.fs", "SC1_PosBarva");
	shaderManager.loadShaderProgram("Shaders/vertexShader.vs", "Shaders/ShaderGreen.fs", "SC1_Green");

	shaderManager.loadShaderProgram("Shaders/vertexShader.vs", "Shaders/ShaderGreen.fs", "SC2_Green");
	shaderManager.loadShaderProgram("Shaders/lightShader.vs", "Shaders/lambertShader.fs", "SC2_LambertLight");
	shaderManager.loadShaderProgram("Shaders/lightShader.vs", "Shaders/phongShader.fs", "SC2_PhongLight");
	shaderManager.loadShaderProgram("Shaders/lightShader.vs", "Shaders/blinnShader.fs", "SC2_BlinnLight");
}

void Application::createModels()
{
	float points[] = {
	 0.0f, 0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
	};
	modelManager.loadModel(tree, sizeof(tree), 6, "Tree");
	modelManager.loadModel(bushes, sizeof(bushes), 6, "Bushes");
	modelManager.loadModel(sphere, sizeof(sphere), 6, "Sphere");
	modelManager.loadModel(gift, sizeof(gift), 6, "Gift");
	modelManager.loadModel(suziFlat, sizeof(suziFlat), 6, "SuziFlat");
	modelManager.loadModel(points, sizeof(points), 3, "Triangle");
}

void Application::createScenes()
{
	std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms0 = {
		shaderManager.getShaderProgram("SC0_Green"),
	};

	std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms1 = {
		shaderManager.getShaderProgram("SC1_PosBarva"),
		shaderManager.getShaderProgram("SC1_Green"),
	};

	std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms2 = {
		shaderManager.getShaderProgram("SC2_Green"),
		shaderManager.getShaderProgram("SC2_LambertLight"),
		shaderManager.getShaderProgram("SC2_PhongLight"),
		shaderManager.getShaderProgram("SC2_BlinnLight"),
	};

	// Scene 0 Triangle
	std::vector<std::shared_ptr<DrawableObject>> objects0 = {
		std::make_shared<DrawableObject>(modelManager.getModel("Triangle"), shaderManager.getShaderProgram("SC0_Green")),
	};

	objects0[0]->addTransformation(std::make_unique<Translation>(glm::vec3(0, 0, -3)));

	// Random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> pos(-50.0f, 50.0f);
	std::uniform_real_distribution<float> scale(0.7f, 1.7f);

	// Scene 1 Forest
	std::vector<std::shared_ptr<DrawableObject>> objects1;
	for (size_t i = 0; i < 50; i++)
	{
		objects1.push_back(std::make_shared<DrawableObject>(modelManager.getModel("Tree"),
			shaderManager.getShaderProgram("SC1_PosBarva")));


		objects1.push_back(std::make_shared<DrawableObject>(modelManager.getModel("Bushes"),
			shaderManager.getShaderProgram("SC1_Green")));
	}

	size_t i = 0;
	for (auto& object : objects1) {
		object->addTransformation(std::make_unique<Scale>(glm::vec3(scale(gen))));

		float x = pos(gen);
		float z = pos(gen);
		object->addTransformation(std::make_unique<Translation>(glm::vec3(x, 0, z)));

		if (i % 4 == 0)
			object->addTransformation(std::make_unique<Rotation>(scale(gen) / 2, glm::vec3(0, 1, 0)), true);
		++i;
	}

	///// Scene 2 Spheres 4x
	std::vector<std::shared_ptr<DrawableObject>> objects2 = {
		std::make_shared<DrawableObject>(modelManager.getModel("Sphere"), shaderManager.getShaderProgram("SC2_Green")),
		std::make_shared<DrawableObject>(modelManager.getModel("Sphere"), shaderManager.getShaderProgram("SC2_LambertLight")),
		std::make_shared<DrawableObject>(modelManager.getModel("Sphere"), shaderManager.getShaderProgram("SC2_PhongLight")),
		std::make_shared<DrawableObject>(modelManager.getModel("Sphere"), shaderManager.getShaderProgram("SC2_BlinnLight")),
	};

	i = 0;
	for (auto& object : objects2) {
		object->addTransformation(std::make_unique<Rotation>(90 * i++, glm::vec3(0, 0, 1)));
		object->addTransformation(std::make_unique<Translation>(glm::vec3(0, 2, -2.5f)));
	}

	Scenes.push_back(std::make_shared<Scene>(shaderPrograms0, objects0));
	Scenes.push_back(std::make_shared<Scene>(shaderPrograms1, objects1));
	Scenes.push_back(std::make_shared<Scene>(shaderPrograms2, objects2));

	currentCamera = Scenes[currentScene]->getCamera();
}

void Application::run()
{
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();

		// update camera movement
		currentCamera->move(keys);

		// render scene
		Scenes[currentScene]->render();

		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);

		//std::cout << "FPS: " << 1 / deltaTime << std::endl;
	}
}

float Application::getDeltaTime() { return deltaTime; }
