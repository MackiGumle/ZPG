#pragma once
#include <GL/glew.h>
#include <iostream>

class Model {
public:
	Model(float points[], size_t numVertices, size_t stride, std::string m_name);
	~Model();

	void render();

private:
	GLuint m_vbo;
	GLuint m_vao;
	size_t m_numVertices;
	size_t stride;
	std::string m_name;
};

