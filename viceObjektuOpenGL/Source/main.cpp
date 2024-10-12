//Include GLEW
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


//GLM test

//// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
//
//// Camera matrix
//glm::mat4 View = glm::lookAt(
//	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
//	glm::vec3(0, 0, 0), // and looks at the origin
//	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
//);
//// Model matrix : an identity matrix (model will be at the origin)
//glm::mat4 Model = glm::mat4(1.0f);


float points[] = {
	0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

float firstTriangle[] = {
		-0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left 
		-0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
		-0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top 
};

float secondTriangle[] = {
		0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
		0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
		0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top 
};

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"out vec3 color;"
"void main () {"
//"     gl_Position = vec4 (vp, 1.0);"
"     gl_Position = vec4 (vp.x, vp.y, vp.z, 1.0);"
"     color = vc;"
"}";

const char* fragment_shader =
"#version 330\n"
"in vec3 color;"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (color.x, color.y, color.z, 1.0);"
"}";



int main(void)
{
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	Application app;
	app.initialization(1920, 1080, "ZPG", NULL, NULL);

	app.createShaders();
	app.createModels();
	app.createScenes();
	app.run();

}
