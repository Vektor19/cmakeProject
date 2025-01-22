#include "ResourceManager.h"
#include "../renderer/ShaderProgram.h"
#include "../renderer/Texture2D.h"
#include "../renderer/Sprite.h"
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

	std::shared_ptr<renderer::Sprite> ResourcesManager::loadSprite(const std::string& spriteName, const std::string& textureName, const std::string& shaderProgramName, const unsigned int width, const unsigned int height, const std::string& subTextureName)
	{
		auto pTexture = this->getTexture(textureName);
		if (!pTexture)
		{
			std::cerr << "Can't find texture: " << textureName << " for sprite: " << spriteName << std::endl;
			return nullptr;
		}
		auto pShaderProgram = this->getShaderProgram(shaderProgramName);
		if (!pShaderProgram)
		{
			std::cerr << "Can't find shaderProgram: " << shaderProgramName << " for sprite: " << spriteName << std::endl;
			return nullptr;
		}
		std::shared_ptr<renderer::Sprite> pSprite = m_spritesMap.emplace(spriteName, std::make_shared<renderer::Sprite>(pTexture, subTextureName, pShaderProgram, glm::vec2(0.f, 0.f), glm::vec2(width, height))).first->second;
		return pSprite;
	}

	std::shared_ptr<renderer::Sprite> ResourcesManager::getSprite(const std::string& spriteName)
	{
		SpriteMap::const_iterator it = m_spritesMap.find(spriteName);
		if (it != m_spritesMap.end())
		{
			return it->second;
		}
		std::cerr << "Can't find sprite: " << spriteName << std::endl;
		return nullptr;
	}

	std::shared_ptr<renderer::Texture2D> ResourcesManager::loadTextureAtlas(const std::string& textureName,
																			const std::string& textureRelativePath,
																			const unsigned int subTextureWidth,
																			const unsigned int subTextureHeight,
																			std::vector<std::string>& subTexturesNames)
	{
		auto pTexture = this->loadTexture(textureName, textureRelativePath);
		if (pTexture)
		{
			unsigned int width = pTexture->getWidth();
			unsigned int height = pTexture->getHeight();
			unsigned int offsetX = 0;
			unsigned int offsetY = 0;
			for (auto& subtextureName : subTexturesNames)
			{
				pTexture->addSubtexture(subtextureName,
					glm::vec2(static_cast<float>(offsetX) / width, static_cast<float>(height - offsetY - subTextureHeight) / height),
					glm::vec2(static_cast<float>(offsetX + subTextureWidth) / width, static_cast<float>(height - offsetY) / height));
				offsetX += subTextureWidth;
				if (offsetX>= width)
				{
					offsetX = 0;
					offsetY += subTextureHeight;
				}
			}
		}
		return pTexture;
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