#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <iostream>

namespace renderer {
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		bool isCompiled() const { return m_isCompiled; }
		void use() const;
		void setInt(const std::string& name, const GLuint value);
		void setMatrix(const std::string& name, const glm::mat4& matrix);

		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderId);

		bool m_isCompiled = false;
		GLuint m_programId;
	};
}