#pragma once
#include <unordered_set>
#include <memory>

class GameObject;
class Level;
namespace physics
{
	class PhysicsEngine
	{
	public:
		PhysicsEngine() = delete;
		~PhysicsEngine() = delete;
		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine(PhysicsEngine&&) = delete;
		PhysicsEngine& operator=(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&&) = delete;

		static void init();
		static void terminate();
		static void update(const double delta);
		static void addDynamicObject(std::shared_ptr<GameObject> pGameObject);
		static void setCurrentLevel(std::shared_ptr<Level> pLevel);
	private:
		static std::unordered_set<std::shared_ptr<GameObject>> m_dynamicObjects;
		static std::shared_ptr<Level> m_pLevel;
	};
}