#include "ResourceManager.h"
#include "../renderer/ShaderProgram.h"
#include "../renderer/Texture2D.h"
#include "../renderer/Sprite.h"
#include "../renderer/AnimatedSprite.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

namespace resources {
	ResourcesManager::ShaderPogramMap ResourcesManager::m_shaderPrograms;
	ResourcesManager::TextureMap ResourcesManager::m_texturesMap;
	ResourcesManager::SpriteMap ResourcesManager::m_spritesMap;
	ResourcesManager::AnimatedSpriteMap ResourcesManager::m_animatedSpritesMap;
	std::string ResourcesManager::m_path;

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

	std::shared_ptr<renderer::ShaderProgram> ResourcesManager::getShaderProgram(const std::string& shaderProgramName)
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

	std::shared_ptr<renderer::Sprite> ResourcesManager::loadSprite(const std::string& spriteName, const std::string& textureName, const std::string& shaderProgramName, const std::string& subTextureName)
	{
		auto pTexture = getTexture(textureName);
		if (!pTexture)
		{
			std::cerr << "Can't find texture: " << textureName << " for sprite: " << spriteName << std::endl;
			return nullptr;
		}
		auto pShaderProgram = getShaderProgram(shaderProgramName);
		if (!pShaderProgram)
		{
			std::cerr << "Can't find shaderProgram: " << shaderProgramName << " for sprite: " << spriteName << std::endl;
			return nullptr;
		}
		std::shared_ptr<renderer::Sprite> pSprite = m_spritesMap.emplace(spriteName, std::make_shared<renderer::Sprite>(pTexture, subTextureName, pShaderProgram)).first->second;
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

	std::shared_ptr<renderer::AnimatedSprite> ResourcesManager::loadAnimatedSprite(const std::string& spriteName, const std::string& textureName, const std::string& shaderProgramName, const std::string& subTextureName)
	{
		auto pTexture = getTexture(textureName);
		if (!pTexture)
		{
			std::cerr << "Can't find texture: " << textureName << " for animated sprite: " << spriteName << std::endl;
			return nullptr;
		}
		auto pShaderProgram = getShaderProgram(shaderProgramName);
		if (!pShaderProgram)
		{
			std::cerr << "Can't find shaderProgram: " << shaderProgramName << " for sprite: " << spriteName << std::endl;
			return nullptr;
		}
		std::shared_ptr<renderer::AnimatedSprite> pSprite = m_animatedSpritesMap.emplace(spriteName, std::make_shared<renderer::AnimatedSprite>(pTexture, subTextureName, pShaderProgram)).first->second;
		return pSprite;
	}

	std::shared_ptr<renderer::AnimatedSprite> ResourcesManager::getAnimatedSprite(const std::string& spriteName)
	{
		AnimatedSpriteMap::const_iterator it = m_animatedSpritesMap.find(spriteName);
		if (it != m_animatedSpritesMap.end())
		{
			return it->second;
		}
		std::cerr << "Can't find animated sprite: " << spriteName << std::endl;
		return nullptr;
	}

	std::shared_ptr<renderer::Texture2D> ResourcesManager::loadTextureAtlas(const std::string& textureName,
																			const std::string& textureRelativePath,
																			const unsigned int subTextureWidth,
																			const unsigned int subTextureHeight,
																			std::vector<std::string>& subTexturesNames)
	{
		auto pTexture = loadTexture(textureName, textureRelativePath);
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

	void ResourcesManager::unloadAllResources()
	{
		m_animatedSpritesMap.clear();
		m_shaderPrograms.clear();
		m_texturesMap.clear();
		m_spritesMap.clear();
	}

	bool ResourcesManager::loadJSONResources(const std::string& jsonPath)
	{
		std::string jsonString = getFileString(jsonPath);
		if (jsonString.empty())
		{
			std::cerr << "No JSON resources file!" << std::endl;
			return false;
		}
		rapidjson::Document document;
		rapidjson::ParseResult parseResult = document.Parse(jsonString.c_str());
		if (!parseResult)
		{
			std::cerr << "JSON parse error: " << rapidjson::GetParseError_En(parseResult.Code()) << "(" << parseResult.Offset() << ")" << std::endl;
			std::cerr << "In file: " << jsonPath << std::endl;
			return false;
		}
		auto shadersIt = document.FindMember("shaders");
		if (shadersIt != document.MemberEnd())
		{
			for (const auto& currentShader : shadersIt->value.GetArray())
			{
				std::string name = currentShader["name"].GetString();
				std::string filePath_v = currentShader["filePath_v"].GetString();
				std::string filePath_f = currentShader["filePath_f"].GetString();
				loadShaders(name, filePath_v, filePath_f);
			}
		}
		auto textureAtlasesIt = document.FindMember("textureAtlases");
		if (textureAtlasesIt != document.MemberEnd())
		{
			for (const auto& currentTextureAtlas : textureAtlasesIt->value.GetArray())
			{
				std::string name = currentTextureAtlas["name"].GetString();
				std::string filePath = currentTextureAtlas["filePath"].GetString();
				const unsigned int subTextureWidth = currentTextureAtlas["subTextureWidth"].GetUint();
				const unsigned int subTextureHeight = currentTextureAtlas["subTextureHeight"].GetUint();
				const auto subTexturesArray = currentTextureAtlas["subTextures"].GetArray();
				std::vector<std::string> subTextures;
				subTextures.reserve(subTexturesArray.Size());
				for (const auto& subTexture : subTexturesArray)
				{
					subTextures.emplace_back(subTexture.GetString());
				}
				loadTextureAtlas(name, filePath, subTextureWidth, subTextureHeight, std::move(subTextures));
			}
		}
		auto animatedSpritesIt = document.FindMember("animatedSprites");
		if (animatedSpritesIt != document.MemberEnd())
		{
			for (const auto& currentSprite : animatedSpritesIt->value.GetArray())
			{
				std::string name = currentSprite["name"].GetString();
				std::string textureAtlas = currentSprite["textureAtlas"].GetString();
				std::string shader = currentSprite["shader"].GetString();
				const unsigned int initialWidth = currentSprite["initialWidth"].GetUint();
				const unsigned int initialHeight = currentSprite["initialHeight"].GetUint();
				std::string initialSubTexture = currentSprite["initialSubTexture"].GetString();
				auto pSprite = loadAnimatedSprite(name, textureAtlas, shader, initialSubTexture);
				if (!pSprite)
				{
					continue;
				}
				const auto statesArray = currentSprite["states"].GetArray();
				for (const auto& currentState : statesArray)
				{
					std::string stateName = currentState["stateName"].GetString();
					const auto framesArray = currentState["frames"].GetArray();
					std::vector<std::pair<std::string, uint64_t>> state;

					for (const auto& currentFrame : framesArray)
					{
						std::string subTexture = currentFrame["subTexture"].GetString();
						unsigned int duration = currentFrame["duration"].GetUint64();
						state.emplace_back(std::make_pair<std::string, uint64_t>(std::move(subTexture), duration));
					}
					pSprite->addState(stateName, std::move(state));
				}
			}
		}

		auto levelsIt = document.FindMember("levels");
		if (levelsIt != document.MemberEnd())
		{
			for (const auto& currentLevel : levelsIt->value.GetArray())
			{
				const auto description = currentLevel["description"].GetArray();
				std::vector<std::string> levelRows;
				levelRows.reserve(description.Size());
				size_t maxRowLength = 0;
				for (const auto& currentRow : description)
				{
					levelRows.emplace_back(currentRow.GetString());
					if (maxRowLength < levelRows.back().length())
					{
						maxRowLength = levelRows.back().length();
					}
				}
				for (auto& currentRow : levelRows)
				{
					while (currentRow.length()< maxRowLength)
					{
						currentRow.append("D");
					}
				}
				m_levelsDescriptions.emplace_back(std::move(levelRows));
			}
		}
		return true;
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