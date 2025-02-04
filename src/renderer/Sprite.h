#pragma once
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

namespace renderer
{
	class ShaderProgram;
	class Texture2D;

	class Sprite
	{
	public:
		Sprite(std::shared_ptr<Texture2D> pTexture,
			const std::string& initialSubtextureName,
			std::shared_ptr<ShaderProgram> pShaderProgam);

		~Sprite();
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		virtual void render(const glm::vec2& position, const glm::vec2& size, const float rotation) const;
	protected:
		std::shared_ptr<ShaderProgram> m_pShaderProgam;
		std::shared_ptr<Texture2D> m_pTexture;

		VertexBuffer m_vertexCoordsBuffer;
		VertexBuffer m_textureCoordsBuffer;
		IndexBuffer m_indexBuffer;
		VertexArray m_vertexArray;
	};
}