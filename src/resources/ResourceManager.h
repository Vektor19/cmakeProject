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
		ResourcesManager(const ResourcesManager&) = delete;
		ResourcesManager(ResourcesManager&&) = delete;
		ResourcesManager& operator=(const ResourcesManager&) = delete;
		ResourcesManager& operator=(ResourcesManager&&) = delete;

		static ResourcesManager* get_instance();
		static void destroy();

		void setExecutablePath(const std::string& path);
		std::shared_ptr<renderer::ShaderProgram> loadShaders(const std::string& shaderProgramName, const std::string& vertexPath, const std::string& fragmentPath);
		std::shared_ptr<renderer::ShaderProgram> getShaderProgram(const std::string& shaderProgramName) const;
		std::shared_ptr<renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& textureRelativePath);
		std::shared_ptr<renderer::Texture2D> getTexture(const std::string& textureName);
		std::shared_ptr<renderer::Sprite> loadSprite(const std::string& spriteName,
													const std::string& textureName,
													const std::string& shaderProgramName,
													const unsigned int width,
													const unsigned int height,
													const std::string& subTextureName="default");
		std::shared_ptr<renderer::Sprite> getSprite(const std::string& spriteName);
		std::shared_ptr<renderer::Texture2D> loadTextureAtlas(const std::string& textureName,
															  const std::string& textureRelativePath,
															  const unsigned int subTextureWidth,
															  const unsigned int subTextureHeight,
															  std::vector<std::string>& subTexturesNames);

	private:
		std::string m_path;
		static ResourcesManager* m_pInstance;
		typedef std::map<std::string, std::shared_ptr<renderer::ShaderProgram>> ShaderPogramMap;
		typedef std::map<std::string, std::shared_ptr<renderer::Texture2D>> TextureMap;
		typedef std::map<std::string, std::shared_ptr<renderer::Sprite>> SpriteMap;
		ShaderPogramMap m_shaderPrograms;
		TextureMap m_texturesMap;
		SpriteMap m_spritesMap;
		ResourcesManager() = default;
		std::string getFileString(const std::string& relativeFilePath);
	};
}