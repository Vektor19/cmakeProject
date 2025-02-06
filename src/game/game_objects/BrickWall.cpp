#include "BrickWall.h"
#include "../../renderer/Sprite.h"

BrickWall::BrickWall(const EBrickWallType eBrickWallType, 
	const std::shared_ptr<renderer::Sprite> pSprite,
	const glm::vec2& position,
	const glm::vec2& size,
	const float rotation)
	: GameObject(position, size, rotation)
	, m_currentSprite(pSprite)
{
}

void BrickWall::render() const
{
	m_currentSprite->render(m_position, m_size, m_rotation);
}

void BrickWall::update(const uint64_t delta)
{
}
