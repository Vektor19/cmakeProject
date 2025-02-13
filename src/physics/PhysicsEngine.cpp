#include "PhysicsEngine.h"
#include "../game/game_objects/GameObject.h"
#include "../game/Level.h"
#include "collision/CollisionManager.h"
#include <iostream>
namespace physics{
	std::unordered_set<std::shared_ptr<GameObject>> PhysicsEngine::m_dynamicObjects;
	std::shared_ptr<Level> PhysicsEngine::m_pLevel;
	void PhysicsEngine::init()
	{
	}

	void PhysicsEngine::terminate()
	{
		m_dynamicObjects.clear();
	}

	void PhysicsEngine::update(const double delta)
	{
		for (auto& currentGameObject : m_dynamicObjects)
		{
			if (currentGameObject->getCurrentVelocity()>0)
			{
				glm::vec2 newPosition = currentGameObject->getCurrentPosition() + currentGameObject->getCurrentDirection() * static_cast<float>(currentGameObject->getCurrentVelocity() * delta);
				auto& objectsToCheck = m_pLevel->getObjectsInArea(newPosition, newPosition + currentGameObject->getSize());

				bool hasCollision = false;
				if (!objectsToCheck.empty())
				{
					for (auto& objectToCheck : objectsToCheck)
					{
						if (CollisionManager::checkCollision(currentGameObject->getColliders(), newPosition, objectToCheck->getColliders(), objectToCheck->getCurrentPosition()))
						{
							hasCollision = true;
							break;
						}
					}
				}
				if (!hasCollision)
				{
					currentGameObject->getCurrentPosition() = newPosition;
				}
			}
		}
	}

	void PhysicsEngine::addDynamicObject(std::shared_ptr<GameObject> pGameObject)
	{
		m_dynamicObjects.insert(std::move(pGameObject));
	}
	void PhysicsEngine::setCurrentLevel(std::shared_ptr<Level> pLevel)
	{
		m_pLevel.swap(pLevel);
	}
}