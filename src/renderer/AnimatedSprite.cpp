#include "AnimatedSprite.h"
#include "Texture2D.h"
#include <iostream>
namespace renderer
{
	AnimatedSprite::AnimatedSprite(std::shared_ptr<Texture2D> pTexture,
		const std::string& initialSubtextureName,
		std::shared_ptr<ShaderProgram> pShaderProgam,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation)
		: Sprite(std::move(pTexture), initialSubtextureName, std::move(pShaderProgam), position, size, rotation)
	{
		m_currentAnimationStateDuration = m_animationStatesDurationsMap.cend();
	}
	void AnimatedSprite::addState(const std::string& stateName, std::vector<std::pair<std::string, uint64_t>>& subTextureDurations)
	{
		m_animationStatesDurationsMap.emplace(stateName, std::move(subTextureDurations));
	}
	void AnimatedSprite::setState(const std::string& stateName)
	{
		auto &it = m_animationStatesDurationsMap.find(stateName);
		if (it == m_animationStatesDurationsMap.cend())
		{
			std::cerr << "Can't find animation state " << stateName << std::endl;
			return;
		}
		if (it != m_currentAnimationStateDuration)
		{
			m_currentFrame = 0;
			m_currentAnimationTime = 0;
			m_currentAnimationStateDuration = it;
			m_dirty = true;
		}
	}
	void AnimatedSprite::update(const uint64_t& delta)
	{
		if (m_currentAnimationStateDuration != m_animationStatesDurationsMap.cend())
		{
			m_currentAnimationTime += delta;
			while (m_currentAnimationTime >= m_currentAnimationStateDuration->second[m_currentFrame].second)
			{
				m_currentAnimationTime -= m_currentAnimationStateDuration->second[m_currentFrame].second;
				++m_currentFrame;
				m_dirty = true;
				if (m_currentFrame == m_currentAnimationStateDuration->second.size())
				{
					m_currentFrame = 0;
				}
			}
		}
		
	}
	void AnimatedSprite::render() const
	{
		if (m_dirty)
		{
			auto subTexture = m_pTexture->getSubtexture(m_currentAnimationStateDuration->second[m_currentFrame].first);
			const GLfloat texCoords[] = {
				subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
				subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.rightTopUV.y,

				subTexture.rightTopUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
				subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			};
			glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(texCoords), &texCoords);
			m_dirty = false;
		}
		Sprite::render();
	}
	AnimatedSprite::~AnimatedSprite()
	{
	}
}
