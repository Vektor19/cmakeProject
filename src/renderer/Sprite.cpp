#include "Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace renderer
{
	Sprite::Sprite(std::shared_ptr<Texture2D> pTexture,
		const std::string& initialSubtextureName,
		std::shared_ptr<ShaderProgram> pShaderProgam,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation
		)
		: m_pTexture(std::move(pTexture))
		, m_pShaderProgam(std::move(pShaderProgam))
		, m_position(position)
		, m_size(size)
		, m_rotation(rotation)
	{
		const GLfloat vertexCoords[] = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
		};

		auto subTexture = m_pTexture->getSubtexture(initialSubtextureName);
		const GLfloat texCoords[] = {
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
		};

		const GLuint indeces[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_vertexCoordsBuffer.init(vertexCoords, 2 * 4 * sizeof(GLfloat));
		VertexBufferLayout vertexCoordsLayout;
		vertexCoordsLayout.addElementLayoutFloat(2, false);
		m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);

		m_textureCoordsBuffer.init(texCoords, 2 * 4 * sizeof(GLfloat));
		VertexBufferLayout textureCoordsLayout;
		textureCoordsLayout.addElementLayoutFloat(2, false);
		m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);

		m_indexBuffer.init(indeces, 6 * sizeof(GLuint));


		m_vertexArray.unbind();
		m_indexBuffer.unbind();
	}
	Sprite::~Sprite()
	{
		
	}
	void Sprite::render() const
	{
		m_pShaderProgam->use();

		glm::mat4 modelMat(1.f);
		modelMat = glm::translate(modelMat, glm::vec3(m_position, 0.f));
		modelMat = glm::translate(modelMat, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.f));
		modelMat = glm::rotate(modelMat, glm::radians(m_rotation), glm::vec3(0.f,0.f,1.f));
		modelMat = glm::translate(modelMat, glm::vec3(-0.5f*m_size.x, -0.5f * m_size.y, 0.f));
		modelMat = glm::scale(modelMat, glm::vec3(m_size, 1.0f));

		m_vertexArray.bind();
		m_pShaderProgam->setMatrix("modelMat", modelMat);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();
		m_vertexArray.unbind();
	}
	void Sprite::setPosition(const glm::vec2& position)
	{
		this->m_position = position;
	}
	void Sprite::setSize(const glm::vec2& size)
	{
		this->m_size = size;
	}
	void Sprite::setRotation(const float rotation)
	{
		this->m_rotation = rotation;
	}
}
