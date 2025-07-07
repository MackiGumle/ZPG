// Author: SIS0049 - Oliver Siskan
#pragma once
#include <GL/glew.h>
#include <iostream>
#include <assimp/mesh.h>



struct Vertex
{
	float Position[3];
	float Normal[3];
	float Texture[2];
	float Tangent[3];
};


class Model {
public:
	Model() = default;
	Model(const float points[], size_t numBytes, size_t stride, std::string m_name);
	Model(const aiMesh* mesh, Vertex* pVertices, unsigned int* pIndices, std::string m_name);
	~Model();

	std::string getName() const;
	size_t getNumVertices() const;
	void render() const; 

private:
	GLuint vbo;
	GLuint ibo;
	GLuint vao;
	size_t numVertices;
	size_t numIndices;
	size_t stride;
	std::string name;
};

