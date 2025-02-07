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
		struct FrameDescription
		{
			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;
			double duration;
			FrameDescription(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV, const double _duration)
				:leftBottomUV(_leftBottomUV), rightTopUV(_rightTopUV), duration(_duration)
			{}
		};
		Sprite(std::shared_ptr<Texture2D> pTexture,
			const std::string& initialSubtextureName,
			std::shared_ptr<ShaderProgram> pShaderProgam);

		~Sprite();
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		void render(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer = 0, size_t frameIndex=0) const;
		void setFrames(std::vector<FrameDescription> framesDescriptions);
		double getFrameDuration(const size_t frameIndex) const;
		size_t getFramesCount() const;
	protected:
		std::shared_ptr<ShaderProgram> m_pShaderProgam;
		std::shared_ptr<Texture2D> m_pTexture;

		VertexBuffer m_vertexCoordsBuffer;
		VertexBuffer m_textureCoordsBuffer;
		IndexBuffer m_indexBuffer;
		VertexArray m_vertexArray;

		std::vector<FrameDescription> m_framesDescriptions;
		mutable size_t m_lastFrameIndex;
	};
}