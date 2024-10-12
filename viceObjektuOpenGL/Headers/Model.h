#pragma once
#include <GL/glew.h>
#include <iostream>

class Model {
public:
	Model(const float points[], size_t numVertices, size_t stride, std::string m_name);
	~Model();

	void render() const; 

private:
	GLuint vbo;
	GLuint vao;
	size_t numVertices;
	size_t stride;
	std::string name;
};

