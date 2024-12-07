// Author: SIS0049 - Oliver Siskan
#include "Model.h"

	// 
	Model::Model(const float points[], size_t numBytes, size_t stride, std::string m_name)
		: ibo(0), numVertices(numBytes / sizeof(float) / stride), numIndices(0), stride(stride), name(m_name)
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, numBytes, points, GL_STATIC_DRAW);

		// Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		// Normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// Texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		std::cout << "[i] Created model ->\t" << "name: " << m_name << "\tnumVertices: " << numVertices << "\n";
	}

	Model::Model(const aiMesh* mesh, Vertex* pVertices, unsigned int* pIndices, std::string m_name)
		: numVertices(mesh->mNumVertices), stride(sizeof(Vertex)), name(m_name)
	{
		glGenVertexArrays(1, &vao);

		glGenBuffers(1, &vbo);

		glGenBuffers(1, &ibo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, pVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));

		//Tangent for Normal Map
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

		//Index Buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(vao);

		GLuint err = glGetError();
		if (err != GL_NO_ERROR) {
			std::cout << "GL ERROR: " << err << std::endl;
		}

		numIndices = mesh->mNumFaces * 3;
		std::cout << "[i] Created model from file ->\t" << "name: " << m_name << "\tnumVertices: " << numVertices << "\n";
	}


	Model::~Model()
	{
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		std::cout << "[i] Deleted model ->\t" << "m_name: " << name << "\tnumVertices: " << numVertices << "\n";
	}

	std::string Model::getName() const
	{
		return name;
	}

	size_t Model::getNumVertices() const
	{
		return numVertices;
	}

	void Model::render() const
	{
		glBindVertexArray(vao);

		if (numIndices > 0) {
			glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, numVertices);
		}
		//glDrawArrays(GL_TRIANGLES, 0, numVertices);
	}