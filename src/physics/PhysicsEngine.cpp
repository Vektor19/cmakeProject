#include "PhysicsEngine.h"
#include "../game/game_objects/GameObject.h"
namespace physics{
	std::unordered_set<std::shared_ptr<GameObject>> PhysicsEngine::m_dynamicObjects;
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
				currentGameObject->getCurrentPosition() += currentGameObject->getCurrentDirection() * static_cast<float>(currentGameObject->getCurrentVelocity() * delta);
			}
		}
	}

	void PhysicsEngine::addDynamicObject(std::shared_ptr<GameObject> pGameObject)
	{
		m_dynamicObjects.insert(std::move(pGameObject));
	}
}