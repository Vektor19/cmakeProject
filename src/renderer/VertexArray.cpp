#include "VertexArray.h"

namespace renderer
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_id);
	}
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}
	VertexArray::VertexArray(VertexArray&& other) noexcept
	{
		m_id = other.m_id;
		other.m_id = 0;
	}
	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
	{
		m_id = other.m_id;
		other.m_id = 0;
		// TODO: вставьте здесь оператор return
		return *this;
	}
	void VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
	{
		bind();
		vertexBuffer.bind();
		const auto& layoutElements = layout.getLayoutElements();
		for (size_t i = 0; i < layoutElements.size(); ++i)
		{
			const auto& currentLayoutElement = layoutElements[i];
			GLuint currentAttribIndex = m_elementsCount + i;
			GLbyte* offset = nullptr;
			glEnableVertexAttribArray(currentAttribIndex);
			glVertexAttribPointer(currentAttribIndex, currentLayoutElement.count, currentLayoutElement.type, currentLayoutElement.normalized, layout.getStride(), offset);
			offset += currentLayoutElement.size;
		}
		m_elementsCount += static_cast<unsigned int>(layoutElements.size());
	}
	void VertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}
	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
}