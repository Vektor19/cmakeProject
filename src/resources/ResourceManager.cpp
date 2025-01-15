#include "ResourceManager.h"
#include "../renderer/ShaderProgram.h"
#include "../renderer/Texture2D.h"
#include <fstream>
#include <sstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

namespace resources {

	ResourcesManager* ResourcesManager::m_pInstance = nullptr;
	ResourcesManager* ResourcesManager::get_instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new ResourcesManager;
		}
		return m_pInstance;
	}

	void ResourcesManager::destroy()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	void ResourcesManager::setExecutablePath(const std::string& path)
	{
		size_t found = path.find_last_of("/\\");
		m_path = path.substr(0, found + 1);
	}

	std::shared_ptr<renderer::ShaderProgram> ResourcesManager::loadShaders(const std::string& shaderProgramName, const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexSource = getFileString(vertexPath);
		if (vertexSource.empty())
		{
			std::cerr << "No vertex shader" << std::endl;
			return nullptr;
		}
		std::string fragmentSource = getFileString(fragmentPath);
		if (fragmentPath.empty())
		{
			std::cerr << "No fragment shader" << std::endl;
			return nullptr;
		}
		std::shared_ptr<renderer::ShaderProgram>& newSharedProgram = m_shaderPrograms.emplace(shaderProgramName, std::make_shared<renderer::ShaderProgram>(vertexSource, fragmentSource)).first->second;
		if (newSharedProgram->isCompiled())
		{
			return newSharedProgram;
		}
		std::cerr << "Can't load shader program:\n"
			<< "Vertex: " << vertexPath << "\n"
			<< "Fragment: " << fragmentPath << std::endl;
		return nullptr;
	}

	std::shared_ptr<renderer::ShaderProgram> ResourcesManager::getShaderProgram(const std::string& shaderProgramName) const
	{
		ShaderPogramMap::const_iterator it = m_shaderPrograms.find(shaderProgramName);
		if (it != m_shaderPrograms.end())
		{
			return it->second;
		}
		std::cerr << "Can't find shader program: " << shaderProgramName << std::endl;
		return nullptr;
	}

	std::shared_ptr<renderer::Texture2D> ResourcesManager::loadTexture(const std::string& textureName, const std::string& textureRelativePath)
	{
		int channel = 0;
		int width = 0;
		int height = 0;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* pixels = stbi_load((m_path + textureRelativePath).c_str(), &width, &height, &channel, 0);
		if (!pixels)
		{
			std::cerr << "Can't load texture: " << textureRelativePath << std::endl;
			return nullptr;
		}

		std::shared_ptr<renderer::Texture2D>& newTexture = m_texturesMap.emplace(textureName, std::make_shared<renderer::Texture2D>(width,height, pixels, channel, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;
		stbi_image_free(pixels);
		return newTexture;
	}

	std::shared_ptr<renderer::Texture2D> ResourcesManager::getTexture(const std::string& textureName)
	{
		TextureMap::const_iterator it = m_texturesMap.find(textureName);
		if (it != m_texturesMap.end())
		{
			return it->second;
		}
		std::cerr << "Can't find texture: " << textureName << std::endl;
		return nullptr;
	}

	std::string ResourcesManager::getFileString(const std::string& relativeFilePath)
	{
		std::ifstream f;
		f.open(m_path + relativeFilePath, std::ios::in | std::ios::binary);
		if (!f.is_open())
		{
			std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
			return std::string();
		}
		std::stringstream buffer;
		buffer << f.rdbuf();
		return buffer.str();
	}

}