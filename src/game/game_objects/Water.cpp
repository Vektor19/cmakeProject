#include "Water.h"
#include "../../renderer/Sprite.h"
#include "../../renderer/SpriteAnimator.h"
#include "../../resources/ResourceManager.h"

#include "../../physics/collision/AABBCollider.h"
Water::Water(const glm::vec2& position,
	const glm::vec2& size,
	const float rotation,
	const float layer)
	: GameObject(position, size, rotation, layer)
	, m_blockOffsets{ glm::vec2(0, m_size.y / 2.f),
					   glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
					   glm::vec2(0, 0),
					   glm::vec2(m_size.x / 2.f, 0) }
	, m_sprite(resources::ResourcesManager::getSprite("water"))
	, m_spriteAnimator(std::make_unique<renderer::SpriteAnimator>(m_sprite))
{
	int collisionMask =
		static_cast<int>(physics::AABBCollider::CollisionLayer::Static) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Dynamic) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Bullet);
	m_colliders.reserve(1);
	m_colliders.emplace_back(std::make_unique<physics::AABBCollider>(physics::AABBCollider::CollisionLayer::Dynamic, collisionMask, glm::vec2(0.f, 0.f), m_size));

}

void Water::render() const
{
	renderBlock(EBlockLocation::TopLeft);
	renderBlock(EBlockLocation::TopRight);
	renderBlock(EBlockLocation::BottomLeft);
	renderBlock(EBlockLocation::BottomRight);
}

void Water::update(const double delta)
{
	m_spriteAnimator->update(delta);
}

void Water::renderBlock(EBlockLocation eBlockLocation) const
{
	m_sprite->render(m_position + m_blockOffsets[static_cast<size_t>(eBlockLocation)], m_size / 2.f, m_rotation, m_layer, m_spriteAnimator->getCurrentFrame());
}
