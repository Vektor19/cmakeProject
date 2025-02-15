#include "Ice.h"
#include "../../renderer/Sprite.h"
#include "../../resources/ResourceManager.h"
#include "../../physics/collision/AABBCollider.h"
#include "Bullet.h"
#include "Water.h"

Ice::Ice(const glm::vec2& position,
	const glm::vec2& size,
	const float rotation,
	const float layer)
	: GameObject(position, size, rotation, layer)
	, m_blockOffsets { glm::vec2(0, m_size.y / 2.f),
					   glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
					   glm::vec2(0, 0),
					   glm::vec2(m_size.x / 2.f, 0) }
	, m_sprite(resources::ResourcesManager::getSprite("ice"))
{
	int collisionMask =
		static_cast<int>(physics::AABBCollider::CollisionLayer::Static) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Dynamic) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Bullet);
	m_colliders.reserve(1);
	m_colliders.emplace_back(std::make_unique<physics::AABBCollider>(physics::AABBCollider::CollisionLayer::Static, collisionMask, glm::vec2(0.f, 0.f), m_size));

}

void Ice::render() const
{
	renderBlock(EBlockLocation::TopLeft);
	renderBlock(EBlockLocation::TopRight);
	renderBlock(EBlockLocation::BottomLeft);
	renderBlock(EBlockLocation::BottomRight);
}

void Ice::update(const double delta)
{
}

void Ice::OnCollisionCallback(const std::shared_ptr<GameObject> object, const glm::vec2& collisionPoint)
{
	if (auto bullet = std::dynamic_pointer_cast<Bullet>(object))
	{
		takeDamage();
	}
}

void Ice::takeDamage()
{
	if (!m_parentLevel)
	{
		return;
	}
	m_parentLevel->replaceObject(shared_from_this(), std::make_shared<Water>(m_position, m_size, m_rotation, 0.f));
}

void Ice::setParentLevel(std::shared_ptr<Level> parentLevel)
{
	m_parentLevel = std::move(parentLevel);
}

void Ice::renderBlock(EBlockLocation eBlockLocation) const
{
	m_sprite->render(m_position + m_blockOffsets[static_cast<size_t>(eBlockLocation)], m_size / 2.f, m_rotation, m_layer);
}
