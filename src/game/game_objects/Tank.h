#pragma once
#include <memory>
#include <glm/vec2.hpp>
#include "GameObject.h"
#include "../../renderer/SpriteAnimator.h"
namespace renderer { class Sprite; }
class Tank: public GameObject
{
public:
	enum class EOrientation
	{
		Top,
		Bottom,
		Left,
		Right
	};
	enum class ETankType
	{
		Yellow1,
		Yellow2,
		Yellow3,
		Yellow4,
		White1,
		White2,
		White3,
		White4,
		Green1,
		Green2,
		Green3,
		Green4,
		Green5,
		Green6,
		Green7,
		Green8,
		Red1,
		Red2,
		Red3,
		Red4
	};
	Tank(const ETankType eTankType,
		 const float velocity,
		 const glm::vec2& position,
		 const glm::vec2& size,
	  	 const float rotation = 0);
	

	void render() const override;
	void setOrientation(const EOrientation eOrientation);
	void move(const bool move);
	void update(const uint64_t delta) override;



private:
	EOrientation m_eOrientation;
	std::shared_ptr<renderer::Sprite> m_pSprite_top;
	std::shared_ptr<renderer::Sprite> m_pSprite_bottom;
	std::shared_ptr<renderer::Sprite> m_pSprite_left;
	std::shared_ptr<renderer::Sprite> m_pSprite_right;

	std::unique_ptr<renderer::SpriteAnimator> m_spriteAnimator_top;
	std::unique_ptr<renderer::SpriteAnimator> m_spriteAnimator_bottom;
	std::unique_ptr<renderer::SpriteAnimator> m_spriteAnimator_left;
	std::unique_ptr<renderer::SpriteAnimator> m_spriteAnimator_right;

	bool m_move;
	float m_velocity;
	glm::vec2 m_moveOffset;
};