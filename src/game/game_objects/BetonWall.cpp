#include "BetonWall.h"
#include "../../renderer/Sprite.h"
#include "../../resources/ResourceManager.h"
#include "../../physics/collision/AABBCollider.h"
#include "Bullet.h"
#include <memory>

BetonWall::BetonWall(const EBetonWallType eBetonWallType,
	const glm::vec2& position,
	const glm::vec2& size,
	const float rotation,
	const float layer)
	: GameObject(position, size, rotation, layer)
	, m_eBrickStates{EBrickState::Destroyed,
					 EBrickState::Destroyed,
					 EBrickState::Destroyed,
					 EBrickState::Destroyed }
	, m_blockOffsets { glm::vec2(0, m_size.y / 2.f),
					   glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
					   glm::vec2(0, 0),
					   glm::vec2(m_size.x / 2.f, 0) }
{
	m_sprites[static_cast<size_t>(EBrickState::All)] = resources::ResourcesManager::getSprite("betonWall");

	int collisionMask =
		static_cast<int>(physics::AABBCollider::CollisionLayer::Dynamic) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Bullet);

	m_colliders.resize(4);
	m_colliders[static_cast<size_t>(EBrickLocation::TopLeft)] =
		std::make_unique<physics::AABBCollider>(physics::AABBCollider::CollisionLayer::Static,
			collisionMask,
			glm::vec2(0.f, m_size.y / 2.f),
			glm::vec2(m_size.x / 2.f, m_size.y));
	m_colliders[static_cast<size_t>(EBrickLocation::TopRight)] =
		std::make_unique<physics::AABBCollider>(physics::AABBCollider::CollisionLayer::Static,
			collisionMask,
			glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
			m_size);
	m_colliders[static_cast<size_t>(EBrickLocation::BottomLeft)] =
		std::make_unique<physics::AABBCollider>(physics::AABBCollider::CollisionLayer::Static,
			collisionMask,
			glm::vec2(0.f, 0.f),
			glm::vec2(m_size.x / 2.f, m_size.y / 2.f));
	m_colliders[static_cast<size_t>(EBrickLocation::BottomRight)] =
		std::make_unique<physics::AABBCollider>(physics::AABBCollider::CollisionLayer::Static,
			collisionMask,
			glm::vec2(m_size.x / 2.f, 0.f),
			glm::vec2(m_size.x, m_size.y / 2.f));
	switch (eBetonWallType)
	{
	case EBetonWallType::All:
		m_eBrickStates.fill(EBrickState::All);
		break;
	case EBetonWallType::Top:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		m_colliders[static_cast<size_t>(EBrickLocation::BottomLeft)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		m_colliders[static_cast<size_t>(EBrickLocation::BottomRight)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		break;
	case EBetonWallType::Bottom:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_colliders[static_cast<size_t>(EBrickLocation::TopLeft)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		m_colliders[static_cast<size_t>(EBrickLocation::TopRight)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		break;
	case EBetonWallType::Left:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_colliders[static_cast<size_t>(EBrickLocation::TopRight)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		m_colliders[static_cast<size_t>(EBrickLocation::BottomRight)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		break;
	case EBetonWallType::Right:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_colliders[static_cast<size_t>(EBrickLocation::TopLeft)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		m_colliders[static_cast<size_t>(EBrickLocation::BottomLeft)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		break;
	case EBetonWallType::TopLeft:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_colliders[static_cast<size_t>(EBrickLocation::TopRight)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		m_colliders[static_cast<size_t>(EBrickLocation::BottomRight)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		m_colliders[static_cast<size_t>(EBrickLocation::BottomLeft)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		break;
	case EBetonWallType::TopRight:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		m_colliders[static_cast<size_t>(EBrickLocation::TopLeft)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		m_colliders[static_cast<size_t>(EBrickLocation::BottomRight)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		m_colliders[static_cast<size_t>(EBrickLocation::BottomLeft)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		break;
	case EBetonWallType::BottomLeft:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_colliders[static_cast<size_t>(EBrickLocation::TopRight)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		m_colliders[static_cast<size_t>(EBrickLocation::BottomRight)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		m_colliders[static_cast<size_t>(EBrickLocation::TopLeft)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		break;
	case EBetonWallType::BottomRight:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_colliders[static_cast<size_t>(EBrickLocation::TopRight)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		m_colliders[static_cast<size_t>(EBrickLocation::TopLeft)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		m_colliders[static_cast<size_t>(EBrickLocation::BottomLeft)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
		break;
	default:
		break;
	}
	
}

void BetonWall::render() const
{
	renderBrick(EBrickLocation::TopLeft);
	renderBrick(EBrickLocation::TopRight);
	renderBrick(EBrickLocation::BottomLeft);
	renderBrick(EBrickLocation::BottomRight);
}

void BetonWall::update(const double delta)
{
}

void BetonWall::OnCollisionCallback(const std::shared_ptr<GameObject> object, const glm::vec2& collisionPoint)
{
	if (auto bullet = std::dynamic_pointer_cast<Bullet>(object))
	{
		takeDamageOnBrick(getBrickLocationByPoint(collisionPoint));
	}
}

void BetonWall::takeDamageOnBrick(BetonWall::EBrickLocation eBrickLocation)
{
	m_eBrickStates[static_cast<size_t>(eBrickLocation)] = EBrickState::Destroyed;
	m_colliders[static_cast<size_t>(eBrickLocation)]->setCollisionLayer(physics::AABBCollider::CollisionLayer::None);
}

BetonWall::EBrickLocation BetonWall::getBrickLocationByPoint(const glm::vec2& point)
{
	if (point.x >= m_position.x && point.x <= m_position.x + m_size.x &&
		point.y >= m_position.y && point.y <= m_position.y + m_size.y)
	{
		if (point.x - m_position.x < m_size.x / 2.f)
		{
			if (point.y - m_position.y < m_size.y / 2.f)
			{
				return BetonWall::EBrickLocation::BottomLeft;
			}
			else
			{
				return BetonWall::EBrickLocation::TopLeft;
			}
		}
		else
		{
			if (point.y - m_position.y < m_size.y / 2.f)
			{
				return BetonWall::EBrickLocation::BottomRight;
			}
			else
			{
				return BetonWall::EBrickLocation::TopRight;
			}
		}
	}
	return BetonWall::EBrickLocation::TopLeft;
}

void BetonWall::renderBrick(EBrickLocation eBrickLocation) const
{
	const EBrickState state = m_eBrickStates[static_cast<size_t>(eBrickLocation)];
	if (state != EBrickState::Destroyed)
	{
		m_sprites[static_cast<size_t>(state)]->render(m_position + m_blockOffsets[static_cast<size_t>(eBrickLocation)], m_size/2.f, m_rotation, m_layer);
	}
}
