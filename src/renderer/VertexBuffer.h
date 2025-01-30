#pragma once
#include <glad/glad.h>
namespace renderer
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&& other) noexcept;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept;
		void init(const void* data, const unsigned int size);
		void update(const void* data, const unsigned int size) const;
		void bind() const;
		void unbind() const;
	private:
		GLuint m_id;
	};
}