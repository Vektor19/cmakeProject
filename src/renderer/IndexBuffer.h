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
		IndexBuffer(IndexBuffer&& other) noexcept;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept;
		void init(const void* data, const unsigned int size);
		void bind() const;
		void unbind() const;
		unsigned int getCount() const { return m_count; }
	private:
		GLuint m_id;
		unsigned int m_count;
	};
}