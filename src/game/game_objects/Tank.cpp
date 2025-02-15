#include "Tank.h"
#include "Bullet.h"
#include "../../renderer/Sprite.h"
#include "../../resources/ResourceManager.h"
#include "../../physics/collision/AABBCollider.h"
#include "../../physics/PhysicsEngine.h"
#include "../DynamicObjectsRenderer.h"
#include "../ai/TankAIComponent.h"
Tank::Tank(const ETankType eTankType,
		   const double maxVelocity,
		   const glm::vec2& position,
		   const glm::vec2& size,
		   const float rotation,
		   const float layer,
		   const double hitPoints)
	       : GameObject(position, size, rotation, layer)
		   , m_eOrientation(EOrientation::Top)
		   , m_maxVelocity(maxVelocity)
		   , m_pSprite_respawn(resources::ResourcesManager::getSprite("respawn"))
		   , m_spriteAnimator_respawn(std::make_unique<renderer::SpriteAnimator>(m_pSprite_respawn))
		   , m_pSprite_shield(resources::ResourcesManager::getSprite("shield"))
		   , m_spriteAnimator_shield(std::make_unique<renderer::SpriteAnimator>(m_pSprite_shield))
		   , m_isSpawning(true)
		   , m_hasShield(false)
		   , m_isReloading(true)
		   , m_reloadingDuration(1000)
		   , m_hitPoints(hitPoints)
		   , m_hasAI(false)
{
	std::string spriteTopName;
	std::string spriteBottomName;
	std::string spriteLeftName;
	std::string spriteRightName;
	switch (eTankType)
	{
	case ETankType::Yellow1:
		spriteTopName		= "tankSprite_top";
		spriteBottomName	= "tankSprite_bottom";
		spriteLeftName		= "tankSprite_left";
		spriteRightName		= "tankSprite_right";
	default:
		spriteTopName		= "tankSprite_top";
		spriteBottomName	= "tankSprite_bottom";
		spriteLeftName		= "tankSprite_left";
		spriteRightName		= "tankSprite_right";
		break;
	}
	m_pSprite_top    = resources::ResourcesManager::getSprite(spriteTopName);
	m_pSprite_bottom = resources::ResourcesManager::getSprite(spriteBottomName);
	m_pSprite_left   = resources::ResourcesManager::getSprite(spriteLeftName);
	m_pSprite_right  = resources::ResourcesManager::getSprite(spriteRightName);

	m_spriteAnimator_top	= std::make_unique<renderer::SpriteAnimator>(m_pSprite_top);
	m_spriteAnimator_bottom = std::make_unique<renderer::SpriteAnimator>(m_pSprite_bottom);
	m_spriteAnimator_left	= std::make_unique<renderer::SpriteAnimator>(m_pSprite_left);
	m_spriteAnimator_right	= std::make_unique<renderer::SpriteAnimator>(m_pSprite_right);
	int collisionMask =
		static_cast<int>(physics::AABBCollider::CollisionLayer::Static) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Dynamic) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Bullet) |
		static_cast<int>(physics::AABBCollider::CollisionLayer::Water);
	m_colliders.reserve(1);
	m_colliders.emplace_back(std::make_unique<physics::AABBCollider>(physics::AABBCollider::CollisionLayer::Dynamic, collisionMask, glm::vec2(1.f, 1.f), glm::vec2(m_size.x - 1.f, m_size.y - 1.f)));
	
	m_respawnTimer.setCallBack([&]()
		{
			m_isSpawning = false;
			m_hasShield = true;
			m_isReloading = false;
			if (m_hasAI)
			{
				setVelocity(getMaxVelocity());
			}
			m_shieldTimer.start(2000);
		});

	m_shieldTimer.setCallBack([&]()
		{
			m_hasShield = false;
		});
	m_respawnTimer.start(2000);
	m_reloadingTimer.setCallBack([&]()
		{
			m_isReloading = false;
		});
}

void Tank::render() const
{
	if (m_isSpawning)
	{
		m_pSprite_respawn->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_respawn->getCurrentFrame());
	}
	else
	{
		switch (m_eOrientation)
		{
		case Tank::EOrientation::Top:
			m_pSprite_top->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_top->getCurrentFrame());
			break;
		case Tank::EOrientation::Bottom:
			m_pSprite_bottom->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_bottom->getCurrentFrame());
			break;
		case Tank::EOrientation::Left:
			m_pSprite_left->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_left->getCurrentFrame());
			break;
		case Tank::EOrientation::Right:
			m_pSprite_right->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_right->getCurrentFrame());
			break;
		default:
			break;
		}
		if (m_hasShield)
		{
			m_pSprite_shield->render(m_position, m_size, m_rotation, m_layer+0.1f, m_spriteAnimator_shield->getCurrentFrame());
		}
	}
}

void Tank::setOrientation(const EOrientation eOrientation)
{
	if (m_eOrientation==eOrientation)
	{
		return;
	}
	m_eOrientation = eOrientation;
	switch (m_eOrientation)
	{
	case Tank::EOrientation::Top:
		m_direction.x = 0.f;
		m_direction.y = 1.f;
		break;
	case Tank::EOrientation::Bottom:
		m_direction.x = 0.f;
		m_direction.y = -1.f;
		break;
	case Tank::EOrientation::Left:
		m_direction.x = -1.f;
		m_direction.y = 0.f;
		break;
	case Tank::EOrientation::Right:
		m_direction.x = 1.f;
		m_direction.y = 0.f;
		break;
	default:
		break;
	}
}


void Tank::update(const double delta)
{
	if (m_isSpawning)
	{
		m_spriteAnimator_respawn->update(delta);
		m_respawnTimer.update(delta);
	}
	else
	{
		if (m_hasShield)
		{
			m_spriteAnimator_shield->update(delta);
			m_shieldTimer.update(delta);
		}
		if (m_velocity>0)
		{
			switch (m_eOrientation)
			{
			case Tank::EOrientation::Top:
				m_spriteAnimator_top->update(delta);
				break;
			case Tank::EOrientation::Bottom:
				m_spriteAnimator_bottom->update(delta);
				break;
			case Tank::EOrientation::Left:
				m_spriteAnimator_left->update(delta);
				break;
			case Tank::EOrientation::Right:
				m_spriteAnimator_right->update(delta);
				break;
			default:
				break;
			}
		}
	}
	if (m_aiComponent)
	{
		m_aiComponent->update(delta);
	}
	if (m_isReloading)
	{
		m_reloadingTimer.update(delta);
	}
}

void Tank::setVelocity(const double velocity)
{
	if (!m_isSpawning)
	{
		m_velocity = velocity;
	}
}

void Tank::shoot()
{
	if (!m_isReloading)
	{
		auto bullet = std::make_shared<Bullet>(static_cast<Bullet::EOrientation>(m_eOrientation), 0.1, m_position, glm::vec2(3.f, 4.f), 1.f);
		physics::PhysicsEngine::addDynamicObject(bullet);
		DynamicObjectsRenderer::addDynamicObject(bullet);
		m_isReloading = true;
		m_reloadingTimer.start(m_reloadingDuration);
	}
}

void Tank::OnCollisionCallback(const std::shared_ptr<GameObject> object, const glm::vec2& collisionPoint)
{
	if (auto bullet = std::dynamic_pointer_cast<Bullet>(object))
	{
		takeDamage(bullet->getDamage());
	}
}

void Tank::takeDamage(const double damage)
{
	m_hitPoints-= damage;
	if (m_hitPoints<=0)
	{
		m_isAlive = false;
		physics::PhysicsEngine::addObjectToRemove(shared_from_this());
		DynamicObjectsRenderer::removeDynamicObject(shared_from_this());
		
		if (m_parentLevel)
		{
			m_parentLevel->removeNonMapObject(shared_from_this());
		}
	}
}

void Tank::setParentLevel(std::shared_ptr<Level> parentLevel)
{
	m_parentLevel = std::move(parentLevel);
}

void Tank::initAI()
{
	m_aiComponent = std::make_unique<TankAIComponent>(shared_from_this());
}

void Tank::setTarget(std::shared_ptr<GameObject> target)
{
	m_aiComponent->setTarget(target);
}

void Tank::setHasAI(bool hasAI)
{
	m_hasAI = hasAI;
}

Tank::~Tank()
{
}
