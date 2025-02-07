#pragma once
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include <string>
namespace renderer
{
	class Renderer
	{
	public:
		static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shaderProgram);
		static void setClearColor(float r, float g, float b, float a);
		static void setDepthTest(const bool enable);
		static void clear();
		static std::string getRendererInfo();
		static std::string getGlVersion();
		static void setViewport(unsigned int width, unsigned int height, int marginLeft = 0, int marginBottom = 0);
	};
}