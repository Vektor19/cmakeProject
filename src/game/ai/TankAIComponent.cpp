#include "TankAIComponent.h"
#include "../game_objects/GameObject.h"
#include "../game_objects/Tank.h"
#include <glm/geometric.hpp>

TankAIComponent::TankAIComponent(std::shared_ptr<Tank> owner)
	: m_owner(std::move(owner))
{
	m_owner->setHasAI(true);
	m_owner->setVelocity(m_owner->getMaxVelocity());
}

void TankAIComponent::setTarget(std::shared_ptr<GameObject> target)
{
	m_target = std::move(target);
}

void TankAIComponent::update(const double delta)
{
	if (auto targetShared = m_target.lock()) {
		glm::vec2 targetPos = targetShared->getCurrentPosition();
		glm::vec2 vectorToTarget = targetPos - m_owner->getCurrentPosition();
		if (fabs(vectorToTarget.x) > fabs(vectorToTarget.y))
		{
			if (vectorToTarget.x >= 0)
			{
				m_owner->setOrientation(Tank::EOrientation::Right);
			}
			else
			{
				m_owner->setOrientation(Tank::EOrientation::Left);
			}
		}
		else
		{
			if (vectorToTarget.y >= 0)
			{
				m_owner->setOrientation(Tank::EOrientation::Top);
			}
			else
			{
				m_owner->setOrientation(Tank::EOrientation::Bottom);
			}
		}
		m_owner->shoot();
		if (!targetShared->isAlive())
		{
			m_owner->setVelocity(0);
			m_target.reset();
		}
	}
}
