#pragma once
#include <glad/glad.h>
namespace renderer
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&&) noexcept;
		IndexBuffer& operator=(IndexBuffer&&) noexcept;
		void init(const void* data, const unsigned int size);
		void update(const void* data, const unsigned int size);
		void bind() const;
		void unbind() const;
	private:
		GLuint m_id;
	};
}