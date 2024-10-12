#include "Application.h"
#include "tree.h"
#include "sphere.h"

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
	shaderManager.loadShader("Shaders/vertexShader.glsl", GL_VERTEX_SHADER, "vertexShader");
	shaderManager.loadShader("Shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER, "fragmentShader");
}

void Application::createModels()
{
	modelManager.loadModel(tree, sizeof(tree), 6, "Tree");
}

void Application::createScenes()
{
	std::vector<std::shared_ptr<Model>> models = {
		modelManager.getModel("Tree"),
	};

	std::vector<std::shared_ptr<Shader>> shaders = {
		shaderManager.getShader("vertexShader"),
		shaderManager.getShader("fragmentShader"),
	};

	Scenes.push_back(std::make_shared<Scene>(models, shaders));
}

void Application::run()
{
	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render scene
		Scenes[0]->render();

		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
		
	}
}
