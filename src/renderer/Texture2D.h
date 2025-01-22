#pragma once

#include <glm/vec2.hpp>
#include <glad/glad.h>
#include <string>
#include <map>

namespace renderer
{
	class Texture2D
	{
	public:
		struct Subtexture2D
		{
			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;
			Subtexture2D(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV) : leftBottomUV(_leftBottomUV), rightTopUV(_rightTopUV) {}
			Subtexture2D() : leftBottomUV(0.f), rightTopUV(1.f) {}
		};
		Texture2D(const GLuint width,
				  const GLuint height,
				  const unsigned char* data,
				  const unsigned int channels = 4,
				  const GLenum filter = GL_LINEAR,
				  const GLenum wrapMode = GL_CLAMP_TO_EDGE);
		~Texture2D();

		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D(Texture2D&& texture2d) noexcept;
		Texture2D& operator=(Texture2D&& texture2d) noexcept;

		void bind() const;

		void addSubtexture(const std::string& name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV);
		const Subtexture2D& getSubtexture(const std::string& name) const;

		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }
	private:
		GLuint m_Id;
		GLenum m_format;
		unsigned int m_width;
		unsigned int m_height;
		std::map<std::string, Subtexture2D> m_subTextures;
	};
}