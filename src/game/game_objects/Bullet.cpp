#include "Bullet.h"
#include "../../renderer/Sprite.h"
#include "../../resources/ResourceManager.h"
#include "../../physics/collision/AABBCollider.h"
#include "../Level.h"
Bullet::Bullet(const Bullet::EOrientation eOrientation,
			const double maxVelocity,
			const glm::vec2& position,
			const glm::vec2& size,
			const float layer)
	       : GameObject(position, size, 0, layer)
		   , m_eOrientation(eOrientation)
		   , m_maxVelocity(maxVelocity)
		   , m_pSprite(resources::ResourcesManager::getSprite("bullet_top"))
{

	glm::vec2 m_positionOffset(0);
	glm::vec2 topRightCollider;
	switch (m_eOrientation)
	{
	case Bullet::EOrientation::Top:
		m_rotation = 0.f;
		m_direction.x = 0.f;
		m_direction.y = 1.f;
		m_positionOffset.y = Level::BLOCK_SIZE;
		m_positionOffset.x = fabs(Level::BLOCK_SIZE - m_size.x) / 2.f;
		break;
	case Bullet::EOrientation::Bottom:
		m_rotation = 180.f;
		m_direction.x = 0.f;
		m_direction.y = -1.f;
		m_positionOffset.x = fabs(Level::BLOCK_SIZE - m_size.x) / 2.f;
		m_positionOffset.y = -m_size.y;
		break;
	case Bullet::EOrientation::Left:
		m_rotation = 90.f;
		m_size.x = m_size.y;
		m_size.y = m_size.x;
		m_direction.x = -1.f;
		m_direction.y = 0.f;
		m_positionOffset.y = fabs(Level::BLOCK_SIZE - m_size.y) / 2.f;
		m_positionOffset.x = -m_size.x;
		break;
	case Bullet::EOrientation::Right:
		m_rotation = 270.f;
		m_size.x = m_size.y;
		m_size.y = m_size.x;
		m_direction.x = 1.f;
		m_direction.y = 0.f;
		m_positionOffset.y = fabs(Level::BLOCK_SIZE - m_size.y) / 2.f;
		m_positionOffset.x = Level::BLOCK_SIZE;
		break;
	default:
		m_rotation = 0.f;
		break;
	}
	m_position += m_positionOffset;
	int collisionMask =
		static_cast<int>(physics::AABBCollider::CollisionLayer::Static) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Dynamic) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Bullet) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Trees);
	m_colliders.reserve(1);
	m_colliders.emplace_back(std::make_unique<physics::AABBCollider>(physics::AABBCollider::CollisionLayer::Bullet, collisionMask, glm::vec2(0.f, 0.f), m_size));
	this->setVelocity(m_maxVelocity);
}

void Bullet::render() const
{
	m_pSprite->render(m_position, m_size, m_rotation, m_layer);
}

void Bullet::update(const double delta)
{
	
}

void Bullet::setVelocity(const double velocity)
{
	m_velocity = velocity;
}

Bullet::~Bullet()
{
}
