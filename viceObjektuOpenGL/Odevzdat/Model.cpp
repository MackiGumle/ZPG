#include "Model.h"

	// 
	Model::Model(const float points[], size_t numBytes, size_t stride, std::string m_name)
		: numVertices(numBytes / sizeof(float) / stride), stride(stride), name(m_name)
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, numBytes, points, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		std::cout << "[i] Created model ->\t" << "name: " << m_name << "\tnumVertices: " << numVertices << "\n";
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
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
	}