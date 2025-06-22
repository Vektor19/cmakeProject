#include "Eagle.h"
#include "../../renderer/Sprite.h"
#include "../../resources/ResourceManager.h"
#include "../../physics/collision/AABBCollider.h"
#include "../../physics/PhysicsEngine.h"
#include "../DynamicObjectsRenderer.h"
#include "Bullet.h"
Eagle::Eagle(const glm::vec2& position,
	const glm::vec2& size,
	const float rotation,
	const float layer,
	const double durability)
	: GameObject(position, size, rotation, layer)
	, m_eCurrentEagleState(EEagleState::Alive)
	, m_durability(durability)
{
	m_sprites[static_cast<size_t>(EEagleState::Alive)] = resources::ResourcesManager::getSprite("eagle");
	m_sprites[static_cast<size_t>(EEagleState::Dead)]  = resources::ResourcesManager::getSprite("eagle_dead");
	int collisionMask =
		static_cast<int>(physics::AABBCollider::CollisionLayer::Static) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Dynamic) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Bullet);
	m_colliders.reserve(1);
	m_colliders.emplace_back(std::make_unique<physics::AABBCollider>(physics::AABBCollider::CollisionLayer::Static, collisionMask, glm::vec2(0.f, 0.f), m_size));

}

void Eagle::render() const
{
	m_sprites[static_cast<size_t>(m_eCurrentEagleState)]->render(m_position, m_size, m_rotation, m_layer);
}

void Eagle::OnCollisionCallback(const std::shared_ptr<GameObject> object, const glm::vec2& collisionPoint)
{
	if (auto bullet = std::dynamic_pointer_cast<Bullet>(object))
	{
		takeDamage(bullet->getDamage());
	}
}

void Eagle::takeDamage(const double damage)
{
	m_durability -= damage;
	if (m_durability <= 0)
	{
		m_isAlive = false;
		m_eCurrentEagleState = EEagleState::Dead;
	}
}

void Eagle::update(const double delta)
{
}
