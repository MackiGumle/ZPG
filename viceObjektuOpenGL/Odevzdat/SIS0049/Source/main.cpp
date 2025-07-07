// Author: SIS0049 - Oliver Siskan
﻿//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

#include "Model.h"
#include "Application.h"


int main(void)
{
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	Application app;
	app.initialization(1920, 1080, "ZPG", NULL, NULL);

	app.createShaders();
	app.createModels();
	app.createTextures();
	app.createScenes();
	app.run();

	return 0;
}
