#include "Border.h"
#include "../../renderer/Sprite.h"
#include "../../resources/ResourceManager.h"
#include "../../physics/collision/AABBCollider.h"
Border::Border(const glm::vec2& position,
	const glm::vec2& size,
	const float rotation,
	const float layer)
	: GameObject(position, size, rotation, layer)
	, m_sprite(resources::ResourcesManager::getSprite("border"))
{
	int collisionMask =
		static_cast<int>(physics::AABBCollider::CollisionLayer::Static) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Dynamic) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Bullet);
	m_colliders.reserve(1);
	m_colliders.emplace_back(std::make_unique<physics::AABBCollider>(physics::AABBCollider::CollisionLayer::Dynamic, collisionMask, glm::vec2(0.f, 0.f), m_size));

}

void Border::render() const
{
	m_sprite->render(m_position, m_size, m_rotation, m_layer);
}

void Border::update(const double delta)
{
}
