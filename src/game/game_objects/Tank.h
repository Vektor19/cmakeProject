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
	Tank(std::shared_ptr<renderer::Sprite> pSprite_top,
		 std::shared_ptr<renderer::Sprite> pSprite_bottom,
		 std::shared_ptr<renderer::Sprite> pSprite_left,
		 std::shared_ptr<renderer::Sprite> pSprite_right,
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

	renderer::SpriteAnimator m_spriteAnimator_top;
	renderer::SpriteAnimator m_spriteAnimator_bottom;
	renderer::SpriteAnimator m_spriteAnimator_left;
	renderer::SpriteAnimator m_spriteAnimator_right;

	bool m_move;
	float m_velocity;
	glm::vec2 m_moveOffset;
};