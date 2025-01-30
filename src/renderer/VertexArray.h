#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <glad/glad.h>
namespace renderer
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray(VertexArray&& other) noexcept;
		VertexArray& operator=(VertexArray&& other) noexcept;
		void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
		void bind() const;
		void unbind() const;
	private:
		GLuint m_id = 0;
		unsigned int m_elementsCount = 0;
	};
}