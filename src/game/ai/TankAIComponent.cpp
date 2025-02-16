#include "TankAIComponent.h"
#include "../game_objects/GameObject.h"
#include "../game_objects/Tank.h"
#include <glm/geometric.hpp>
#include <ctime>

TankAIComponent::TankAIComponent(std::shared_ptr<Tank> owner, const float detectionDistance, const EActionType eActionType)
	: m_owner(std::move(owner))
	, AIComponent(detectionDistance, eActionType)
{
	srand(time(NULL));
	m_owner->setHasAI(true);
	m_owner->setVelocity(m_owner->getMaxVelocity());
	m_changeDirrectionTimer.setCallBack([&]() {
		m_owner->setOrientation(static_cast<Tank::EOrientation>(rand() % 4));
		m_changeDirrectionTimer.start(3000);
		});
	m_changeDirrectionTimer.start(3000);
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
		bool isCloseToTarget = isTargetClose(targetShared->getCurrentPosition());
		switch (m_actionType)
		{
		case TankAIComponent::EActionType::None:
			if (m_owner->getCurrentVelocity()>0)
			{
				m_owner->setVelocity(0);
			}
			if (isCloseToTarget)
			{
				m_owner->setVelocity(m_owner->getMaxVelocity());
				m_actionType = TankAIComponent::EActionType::Chase;
			}
			break;
		case TankAIComponent::EActionType::Chase:
			if (isCloseToTarget)
			{
				Tank::EOrientation newOrientation;

				if (fabs(vectorToTarget.x) > fabs(vectorToTarget.y))
				{
					newOrientation = (vectorToTarget.x >= 0) ? Tank::EOrientation::Right : Tank::EOrientation::Left;
				}
				else
				{
					newOrientation = (vectorToTarget.y >= 0) ? Tank::EOrientation::Top : Tank::EOrientation::Bottom;
				}
				if (m_owner->getOrientation() != newOrientation) {
					m_owner->setOrientation(newOrientation);
				}
				m_owner->shoot();
			}
			else
			{
				m_actionType = TankAIComponent::EActionType::Patrol;
			}
			
			break;
		case TankAIComponent::EActionType::Patrol:
			if (isCloseToTarget)
			{
				m_actionType = TankAIComponent::EActionType::Chase;
			}
			else
			{
				m_changeDirrectionTimer.update(delta);
			}
			break;
		default:
			break;
		}
		
		
		if (!targetShared->isAlive())
		{
			m_target.reset();
			m_actionType = TankAIComponent::EActionType::Patrol;
		}
	}
	else if (m_actionType == TankAIComponent::EActionType::Patrol)
	{
		m_changeDirrectionTimer.update(delta);
	}
}

bool TankAIComponent::isTargetClose(const glm::vec2& targetPos)
{
    glm::vec2 ownerPos = m_owner->getCurrentPosition();
    float distance = glm::distance(ownerPos, targetPos);
    return distance <= m_detectionDistance;
}
