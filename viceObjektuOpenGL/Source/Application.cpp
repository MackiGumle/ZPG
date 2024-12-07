#include "Application.h"
#include "tree.h"
#include "bushes.h"
#include "sphere.h"
#include "gift.h"
#include "suzi_flat.h"
#include "plain.h"
#include "Scene.h"
#include "DrawableObject.h"
#include "SceneCreator.h"
#include "TextureManager.h"
#include "Texture.h"
#include "ObserverPattern.h"
#include "TransformFunctions.h"
#include "SkyBox.h"


float Application::windowWidth = 800;
float Application::windowHeight = 600;
float Application::deltaTime = 0.0f;
bool Application::cursorLocked = false;
bool Application::firstMouse = true;


Application::Application() : window(nullptr), shaderManager(ShaderManager()),
modelManager(ModelManager()), currentScene(0), currentCamera(nullptr)//, lastX(0), lastY(0)
{

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
	//printf("resize %d, %d \n", width, height);

	Application::windowWidth = width;
	Application::windowHeight = height;
	glfwGetFramebufferSize(window, &width, &height);

	float ratio = width / (float)height;

	glViewport(0, 0, width, height);
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app) {
		for (auto& scene : app->Scenes)
			scene->getCamera()->setProjectionMatrix(
				scene->getCamera()->getFov()
				, ratio, 0.01f, 500.0f);
	}
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	
	// if cursor is uncloked update cursor position and dont move cam
	if (app && !cursorLocked) {
		app->cursorX = x;
		app->cursorY = y;
		return;
	}
	//if (!cursorLocked) return;


	// if cursor is locked rotate camera and set cursor in the middle of the screen
	static float lastX = windowWidth / 2, lastY = windowHeight / 2;

	if (firstMouse) {
		lastX = static_cast<float>(x);
		lastY = static_cast<float>(y);
		firstMouse = false;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y;

	lastX = x;
	lastY = y;

	//printf("cursor_callback [%f,%f]\n", xoffset, yoffset);

	if (app) {
		app->cursorX = windowWidth / 2;
		app->cursorY = windowHeight / 2;
		app->mouse_input(xoffset, yoffset);
	}

}

void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app) {
		auto fov = app->currentCamera->getFov();
		printf("scroll_callback:\t[%f,%f]\tfov:\t%f\n", xoffset, yoffset, fov);
		app->currentCamera->setFov(fov - yoffset);
	}
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS)
	{
		printf("button_callback [%d,%d,%d]\n", button, action, mode);

		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		if (app) {
			app->mouseButton_input(button, action);
		}
		//Můžeme nastavit vybrané těleso scena->setSelect(index-1);
	}
}

void Application::key_input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		//std::cout << "[i] Key Pressed:\t" << key << "\t" << keys[key] << std::endl;

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

		case GLFW_KEY_C:
			if (cursorLocked)
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

				// if cursor is locked set it to the center of the screen
				cursorX = windowWidth / 2;
				cursorY = windowHeight / 2;
			}
			else
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			firstMouse = true;
			cursorLocked = !cursorLocked;
			break;

		case GLFW_KEY_X:
			Scenes[currentScene]->stopSkyboxMovement();
			break;

		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
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

}

void Application::mouse_input(float xoffset, float yoffset)
{
	currentCamera->rotate(xoffset, yoffset);
	//Scenes[currentScene]->rotateCamera(xoffset, yoffset);
}

void Application::mouseButton_input(int button, int action)
{
	if (action == GLFW_PRESS)
	{
		uint8_t color[4];
		GLfloat depth;
		GLuint index;

		GLint x = (GLint)cursorX;
		GLint y = (GLint)cursorY;
		GLsizei width = Application::getWidth();
		GLsizei height = Application::getHeight();

		int newy = height - y;

		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		//printf("width: %d\theight: %d\n", width, height);
		//printf(
		//	"[i] pixel %d, %d, color r:%u g:%u b:%u a:%u, depth %f, stencil index %u\n",
		//	x, newy, (unsigned int)color[0], (unsigned int)color[1],
		//	(unsigned int)color[2], (unsigned int)color[3], depth, index
		//);

		glm::vec3 screenX = glm::vec3(x, newy, depth);
		
		auto camera = Scenes[currentScene]->getCamera();
		glm::mat4 view = camera->getViewMatrix();
		glm::mat4 projection = camera->getProjectionMatrix();

		glm::vec4 viewPort = glm::vec4(0, 0, width, height);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		//printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

		if (index && currentScene == 2 && !cursorLocked)
		{
			switch (button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
				{
					auto obj = std::make_shared<DrawableObject>(
						modelManager.getModel("Tree"),
						shaderManager.getShaderProgram("SC2_multiple"),
						Material(1, 1, 1, 1, glm::vec3(0, 1, 0.5)));

					obj->addTransformation(std::make_unique<Translation>(pos));

					Scenes[currentScene]->addDrawableObject(obj);
					break;
				}
				case GLFW_MOUSE_BUTTON_RIGHT:
				{
					Scenes[currentScene]->setControlPoint(pos);
					break;
				}
				case GLFW_MOUSE_BUTTON_MIDDLE:
				{
					Scenes[currentScene]->selectObject(index - 1);
					break;
				}
			}
		}
	}
}

void Application::initialization(int w_width, int w_height, const char* w_name, GLFWmonitor* monitor, GLFWwindow* share)
{
	std::cout << "---\tInitializing GLFW\t---" << std::endl;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	windowWidth = w_width;
	windowHeight = w_height;

	window = glfwCreateWindow(windowWidth, windowHeight, w_name, monitor, share);
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

	int width = windowWidth, height = windowHeight;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Sets the key callback
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	//glfwsetwindowfocuscallback(m_window, window_focus_callback);
	//glfwsetwindowiconifycallback(m_window, window_iconify_callback);
	//glfwSetWindowSizeCallback(m_window, window_size_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
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

	// Stencil Buffer
	// glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glEnable(GL_STENCIL_TEST);

	std::cout << "\n\n";
}

void Application::createShaders()
{
	//shaderManager.loadShaderProgram("Shaders/lightShader.vert", "Shaders/mlutiplePhongShader.frag", "SC00_texture");

	shaderManager.loadShaderProgram("Shaders/lightShader.vert", "Shaders/ShaderGreen.frag", "SC0_Green");


	// SC1 4 balls Ligh examples
	shaderManager.loadShaderProgram("Shaders/lightShader.vert", "Shaders/lambertShader.frag", "SC1_LambertLight");
	shaderManager.loadShaderProgram("Shaders/lightShader.vert", "Shaders/phongShader.frag", "SC1_PhongLight");
	shaderManager.loadShaderProgram("Shaders/lightShader.vert", "Shaders/blinnShader.frag", "SC1_BlinnLight");
	shaderManager.loadShaderProgram("Shaders/lightShader.vert", "Shaders/ShaderGreen.frag", "SC1_Green");

	// SC2 Forrest
	shaderManager.loadShaderProgram("Shaders/lightShader.vert", "Shaders/ShaderGreen.frag", "SC2_Green");
	shaderManager.loadShaderProgram("Shaders/lightShader.vert", "Shaders/mlutiplePhongShader.frag", "SC2_multiple");
	shaderManager.loadShaderProgram("Shaders/Skybox.vert", "Shaders/Skybox.frag", "Skybox");
}

void Application::createModels()
{
	float points[] = {
	 0.0f, 0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
	};


	float texturedPyramid[] = {
		//  X      Y     Z      R     G     B     U     V
	0.000000f, -0.500000f, 0.500000f,    -0.872900f, 0.218200f, 0.436400f,   0.836598f, 0.477063f,
	0.000000f, 0.500000f, 0.000000f,     -0.872900f, 0.218200f, 0.436400f,   0.399527f, 0.286309f,
	-0.500000f, -0.500000f, -0.500000f,  -0.872900f, 0.218200f, 0.436400f,   0.836598f, 0.000179f,
	-0.500000f, -0.500000f, -0.500000f,  0.000000f, -1.000000f, 0.000000f,   0.381686f, 0.999821f,
	0.500000f, -0.500000f, -0.500000f,   0.000000f, -1.000000f, 0.000000f,   0.000179f, 0.809067f,
	0.000000f, -0.500000f, 0.500000f,    0.000000f, -1.000000f, 0.000000f,   0.381686f, 0.522937f,
	0.500000f, -0.500000f, -0.500000f,   0.872900f, 0.218200f, 0.436400f,    0.399169f, 0.000179f,
	0.000000f, 0.500000f, 0.000000f,     0.872900f, 0.218200f, 0.436400f,    0.399169f, 0.522579f,
	0.000000f, -0.500000f, 0.500000f,    0.872900f, 0.218200f, 0.436400f,    0.000179f, 0.261379f,
	-0.500000f, -0.500000f, -0.500000f,  0.000000f, 0.447200f, -0.894400f,   0.788901f, 0.477421f,
	0.000000f, 0.500000f, 0.000000f,     0.000000f, 0.447200f, -0.894400f,   0.788901f, 0.999821f,
	0.500000f, -0.500000f, -0.500000f,   0.000000f, 0.447200f, -0.894400f,   0.399527f, 0.651554f
	};

	const float texturedPlain[] = {
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   100.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   100.0f, 100.0f,

	   -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 100.0f,
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   100.0f, 100.0f
	};

	const float skycube[] = {
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
	};


	modelManager.loadModel(tree, sizeof(tree), 6, "Tree");
	modelManager.loadModel(bushes, sizeof(bushes), 6, "Bushes");
	modelManager.loadModel(sphere, sizeof(sphere), 6, "Sphere");
	modelManager.loadModel(gift, sizeof(gift), 6, "Gift");
	modelManager.loadModel(suziFlat, sizeof(suziFlat), 6, "SuziFlat");
	modelManager.loadModel(plain, sizeof(plain), 6, "Plain");
	modelManager.loadModel(points, sizeof(points), 3, "Triangle");
	modelManager.loadModel(texturedPyramid, sizeof(texturedPyramid), 8, "TexturedPyramid");
	modelManager.loadModel(texturedPlain, sizeof(texturedPlain), 8, "TexturedPlain");
	modelManager.loadModel(skycube, sizeof(skycube), 3, "SkyCube");
	modelManager.loadModel("Models/obj/LOGIN.obj", "Login");
	modelManager.loadModel("Models/obj/model.obj", "House");
	modelManager.loadModel("Models/obj/zombie.obj", "Zombie");
	//modelManager.loadModel("Models/obj/angerona.obj", "Angerona");
}

void Application::createTextures()
{
	textureManager.loadTexture("./Textures/default.png", "Default");
	textureManager.loadTexture("wooden_fence.png", "Wood");
	textureManager.loadTexture("grass.png", "Grass");
	textureManager.loadTexture("texture32.png", "Texture");
	textureManager.loadTexture("./Textures/Skybox/Forrest/", "SkyboxForrest", true);
	textureManager.loadTexture("./Textures/Skybox/Space/", "SkyboxSpace", true);
	textureManager.loadTexture("./Models/obj/test.png", "House");
	textureManager.loadTexture("./Models/obj/zombie.png", "Zombie");
	//textureManager.loadTexture("./Models/obj/angerona.png", "Angerona");
}

void Application::createScenes()
{
	SceneCreator sceneCreator;

	sceneCreator.createTestTriangle(Scenes, shaderManager, modelManager);
	sceneCreator.create4Balls(Scenes, shaderManager, modelManager, textureManager);
	sceneCreator.createForrest(Scenes, shaderManager, modelManager, textureManager);


	currentCamera = Scenes[currentScene]->getCamera();
}

void Application::run()
{
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// update camera movement
		currentCamera->move(keys);
		
		// render scene
		Scenes[currentScene]->render();
		
		glfwPollEvents();

		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
		

		//std::cout << "FPS: " << 1 / deltaTime << "\n";
	}
}

float Application::getWidth() { return windowWidth; }

float Application::getHeight() { return windowHeight; }

float Application::getDeltaTime() { return deltaTime; }
