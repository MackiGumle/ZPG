#pragma once
#include <GL/glew.h>
#include <iostream>

class Model {
public:
	Model() = default;
	Model(const float points[], size_t numVertices, size_t stride, std::string m_name);
	~Model();

	std::string getName() const;
	size_t getNumVertices() const;
	void render() const; 

private:
	GLuint vbo;
	GLuint vao;
	size_t numVertices;
	size_t stride;
	std::string name;
};

