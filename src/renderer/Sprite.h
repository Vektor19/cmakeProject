#pragma once
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace renderer
{
	class ShaderProgram;
	class Texture2D;

	class Sprite
	{
	public:
		Sprite(std::shared_ptr<Texture2D> pTexture,
			   const std::string& initialSubtextureName,
			   std::shared_ptr<ShaderProgram> pShaderProgam,
			   const glm::vec2& position = glm::vec2(0.f),
			   const glm::vec2& size = glm::vec2(100.f),
			   const float rotation = 0.f);

		~Sprite();
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		virtual void render() const;
		void setPosition(const glm::vec2& position);
		void setSize(const glm::vec2& size);
		void setRotation(const float rotation);
	protected:
		std::shared_ptr<ShaderProgram> m_pShaderProgam;
		std::shared_ptr<Texture2D> m_pTexture;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotation;

		VertexBuffer m_vertexCoordsBuffer;
		VertexBuffer m_textureCoordsBuffer;
		IndexBuffer m_indexBuffer;
		GLuint m_VAO;
	};
}