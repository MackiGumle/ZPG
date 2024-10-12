#include "Application.h"
#include "tree.h"


Application::Application() : m_window(nullptr), m_shaderManager(nullptr), m_modelManager(nullptr) {
	m_shaderManager = new ShaderManager();
	m_modelManager = new ModelManager();
}

Application::~Application() {
	delete m_shaderManager;
	delete m_modelManager;

	glfwDestroyWindow(m_window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::error_callback(int error, const char* description) { fputs(description, stderr); }

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Application::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Application::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

void Application::initialization(int w_width, int w_height, const char* w_name, GLFWmonitor* monitor, GLFWwindow* share)
{
	std::cout << "---\tInitializing GLFW\t---" << std::endl;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	m_window = glfwCreateWindow(w_width, w_height, w_name, monitor, share);
	if (!m_window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);
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
	glfwGetFramebufferSize(m_window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	// Sets the key callback
	/*glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(m_window, cursor_callback);
	glfwSetMouseButtonCallback(m_window, button_callback);
	glfwSetWindowFocusCallback(m_window, window_focus_callback);
	glfwSetWindowIconifyCallback(m_window, window_iconify_callback);
	glfwSetWindowSizeCallback(m_window, window_size_callback);*/
	std::cout << "\n\n";
}

void Application::createShaders()
{
	if (!m_shaderManager->loadShader("Shaders/vertexShader.glsl", "Shaders/fragmetShader.glsl", "default"))
	{
		std::cout << "[x] Failed to load shader" << std::endl;
		return;
	}

	m_shaderManager->useShaderProgram("default");
}

void Application::createModels()
{
	//float firstTriangle[] = {
	//	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left 
	//	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
	//	-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top 

	//	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left 
	//	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
	//	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top 
	//};

	//float secondTriangle[] = {
	//	0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	//	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	//};

	//m_modelManager->loadModel(firstTriangle, sizeof(firstTriangle), 6, "Trojuhelnik_1");
	//m_modelManager->loadModel(secondTriangle, sizeof(secondTriangle), 6, "Trojuhelnik_2");

	m_modelManager->loadModel(tree, sizeof(tree), 6, "Tree");
}

void Application::run()
{
	while (!glfwWindowShouldClose(m_window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glUseProgram(shaderProgram);
		m_shaderManager->useShaderProgram("default");

		m_modelManager->renderModels();

		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(m_window);
	}
}
