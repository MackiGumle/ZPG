#pragma once
#include <GL/glew.h>
#include <iostream>

namespace ZPG {

	class Model {
	public:
		Model(float points[], size_t numVertices, size_t stride);
		~Model();

		void render();

	private:
		GLuint m_vbo;
		GLuint m_vao;
		size_t m_numVertices;
		size_t stride;
	};

}