#pragma once
#include "Sprite.h"
#include <string>
#include <map>
#include <vector>
#include <chrono>

namespace renderer
{
	class AnimatedSprite: public Sprite
	{
	public:
		AnimatedSprite(std::shared_ptr<Texture2D> pTexture,
				  	   const std::string& initialSubtextureName,
					   std::shared_ptr<ShaderProgram> pShaderProgam);
		void addState(const std::string& stateName, std::vector<std::pair<std::string, uint64_t>>& subTextureDurations);
		void setState(const std::string& stateName);
		void update(const uint64_t& delta);
		void render(const glm::vec2& position, const glm::vec2& size, const float rotation) const override;
		~AnimatedSprite();
	private:
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> m_animationStatesDurationsMap;
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_currentAnimationStateDuration;
		size_t m_currentFrame = 0;
		uint64_t m_currentAnimationTime = 0;
		mutable bool m_dirty = false;
	};
}