#pragma once
#include <memory>
#include <map>
#include <string>

namespace renderer { class ShaderProgram; }

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
	private:
		std::string m_path;
		static ResourcesManager* m_pInstance;
		typedef std::map<std::string, std::shared_ptr<renderer::ShaderProgram>> ShaderPogramMap;
		ShaderPogramMap m_shaderPrograms;
		ResourcesManager() = default;
		std::string getFileString(const std::string& relativeFilePath);
	};
}