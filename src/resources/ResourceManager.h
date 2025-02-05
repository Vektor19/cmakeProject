#pragma once
#include <memory>
#include <map>
#include <string>
#include <vector>

namespace renderer
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
}

namespace resources {
	class ResourcesManager
	{
	public:
		ResourcesManager() = delete;
		~ResourcesManager() = delete;
		ResourcesManager(const ResourcesManager&) = delete;
		ResourcesManager(ResourcesManager&&) = delete;
		ResourcesManager& operator=(const ResourcesManager&) = delete;
		ResourcesManager& operator=(ResourcesManager&&) = delete;


		static void setExecutablePath(const std::string& path);
		static std::shared_ptr<renderer::ShaderProgram> loadShaders(const std::string& shaderProgramName, const std::string& vertexPath, const std::string& fragmentPath);
		static std::shared_ptr<renderer::ShaderProgram> getShaderProgram(const std::string& shaderProgramName);
		static std::shared_ptr<renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& textureRelativePath);
		static std::shared_ptr<renderer::Texture2D> getTexture(const std::string& textureName);
		static std::shared_ptr<renderer::Sprite> loadSprite(const std::string& spriteName,
													const std::string& textureName,
													const std::string& shaderProgramName,
													const std::string& subTextureName="default");
		static std::shared_ptr<renderer::Sprite> getSprite(const std::string& spriteName);
		static std::shared_ptr<renderer::Texture2D> loadTextureAtlas(const std::string& textureName,
															  const std::string& textureRelativePath,
															  const unsigned int subTextureWidth,
															  const unsigned int subTextureHeight,
															  std::vector<std::string>& subTexturesNames);
		static void unloadAllResources();
		static bool loadJSONResources(const std::string& jsonPath);
		static const std::vector<std::vector<std::string>>& getLevelsDescriptions() { return m_levelsDescriptions; }
	private:
		static std::string m_path;
		typedef std::map<std::string, std::shared_ptr<renderer::ShaderProgram>> ShaderPogramMap;
		typedef std::map<std::string, std::shared_ptr<renderer::Texture2D>> TextureMap;
		typedef std::map<std::string, std::shared_ptr<renderer::Sprite>> SpriteMap;
		static std::vector<std::vector<std::string>> m_levelsDescriptions;
		static ShaderPogramMap m_shaderPrograms;
		static TextureMap m_texturesMap;
		static SpriteMap m_spritesMap;
		static std::string getFileString(const std::string& relativeFilePath);
	};
}