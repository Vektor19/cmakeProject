#include "Trees.h"
#include "../../renderer/Sprite.h"
#include "../../resources/ResourceManager.h"
#include "../../physics/collision/AABBCollider.h"
#include "Bullet.h"
Trees::Trees(const glm::vec2& position,
	const glm::vec2& size,
	const float rotation,
	const float layer)
	: GameObject(position, size, rotation, layer)
	, m_blockOffsets { glm::vec2(0, m_size.y / 2.f),
					   glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
					   glm::vec2(0, 0),
					   glm::vec2(m_size.x / 2.f, 0) }
	, m_eTreesState(ETreesState::All)
	, m_sprite(resources::ResourcesManager::getSprite("trees"))
{
	int collisionMask =
		static_cast<int>(physics::AABBCollider::CollisionLayer::Static);
	m_colliders.reserve(1);
	m_colliders.emplace_back(std::make_unique<physics::AABBCollider>(physics::AABBCollider::CollisionLayer::Trees, collisionMask, glm::vec2(0.f, 0.f), m_size));

}

void Trees::render() const
{
	if (m_eTreesState != ETreesState::Destroyed)
	{
		renderBlock(EBlockLocation::TopLeft);
		renderBlock(EBlockLocation::TopRight);
		renderBlock(EBlockLocation::BottomLeft);
		renderBlock(EBlockLocation::BottomRight);
	}
}

void Trees::update(const double delta)
{
}

void Trees::OnCollisionCallback(const std::shared_ptr<GameObject> object, const glm::vec2& collisionPoint)
{
	if (auto bullet = std::dynamic_pointer_cast<Bullet>(object))
	{
		takeDamage();
	}
}

void Trees::takeDamage()
{
	m_eTreesState = ETreesState::Destroyed;
	m_colliders.front()->setCollisionLayer(physics::Collider::CollisionLayer::None);
}

void Trees::renderBlock(EBlockLocation eBlockLocation) const
{
	m_sprite->render(m_position + m_blockOffsets[static_cast<size_t>(eBlockLocation)], m_size / 2.f, m_rotation, m_layer);
}
