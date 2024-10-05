#include "Model.h"

	// 
	Model::Model(float points[], size_t numVertices, size_t stride, std::string m_name)
		: m_numVertices(numVertices), stride(stride), m_name(m_name)
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(float), points, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		std::cout << "[] Created model ->\t" << "m_name: " << m_name << "\tm_numVertices: " << m_numVertices << "\n";
	}

	Model::~Model()
	{
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
		std::cout << "[] Deleted model ->\t" << "m_name: " << m_name << "\tm_numVertices: " << m_numVertices << "\n";
	}

	void Model::render()
	{
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, m_numVertices / stride);
	}