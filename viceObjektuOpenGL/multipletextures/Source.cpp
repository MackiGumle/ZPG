//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h> 

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp>

#include <SOIL.h>

#include "ShaderLoader.h"

using namespace std;

const float triangle [48] = {
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,

    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f
};

static void error_callback(int error, const char* description) { 
    fputs(description, stderr); 
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();


    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height; //perspective matrix
    glViewport(0, 0, width, height);

    //Vertex Array Object (VAO)
    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), &triangle[0], GL_STATIC_DRAW);

    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //enable vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float)*3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 6));

    //Create and compile shaders
    GLuint shaderProgram;
    new ShaderLoader("PhongVertexShader.glsl", "PhongFragmentShader.glsl", &shaderProgram);
    
    //Texture one in texture unit 0
    glActiveTexture(GL_TEXTURE0);
    GLuint textureID1 = SOIL_load_OGL_texture("wooden_fence.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (textureID1 == NULL) {
        std::cout << "An error occurred while loading texture." << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, textureID1);
    
    //Texture two in texture unit 1
    glActiveTexture(GL_TEXTURE1);
    GLuint textureID2 = SOIL_load_OGL_texture("grass.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (textureID2 == NULL) {
        std::cout << "An error occurred while loading texture." << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, textureID2);


    glm::mat4 M = glm::mat4(1.0f);
    
    glUseProgram(shaderProgram);
    glEnable(GL_DEPTH_TEST);
    GLint idTU = glGetUniformLocation(shaderProgram, "textureUnitID");
    float angle = 0;
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(VAO);
        glUniform1i(idTU, 0); // set TU 0
        M = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f));
        M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));
        GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
        glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(VAO);
        glUniform1i(idTU, 1); // set TU 1
        M = glm::translate(glm::mat4(1.0f), glm::vec3(0.4f, 0.0f, 0.0f));
        M = glm::rotate(M, -angle, glm::vec3(0.0f, 0.0f, 1.0f));
        M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));
        idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
        glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 6); 

        glfwPollEvents();
        glfwSwapBuffers(window);
        angle += 0.01f;
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}