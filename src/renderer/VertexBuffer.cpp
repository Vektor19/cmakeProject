#include "VertexBuffer.h"

namespace renderer
{
	VertexBuffer::VertexBuffer():m_id(0)
	{
	}
	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}
	VertexBuffer::VertexBuffer(VertexBuffer&&)
	{

	}
	VertexBuffer& VertexBuffer::operator=(VertexBuffer&&)
	{
		// TODO: вставьте здесь оператор return
	}
	void VertexBuffer::init(const void* data, const unsigned int size)
	{
		glGenBuffers(1, &m_id);
		bind();
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
	}
	void VertexBuffer::update(const void* data, const unsigned int size)
	{
	}
	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}
	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}