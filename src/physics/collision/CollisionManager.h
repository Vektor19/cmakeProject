#pragma once
#include <unordered_set>
#include <memory>
#include "ICollidable.h"
#include "AABBCollider.h"
#include "../../game/game_objects/GameObject.h"
namespace physics
{
	class CollisionManager
	{
	public:
		CollisionManager() = delete;
		~CollisionManager() = delete;
		CollisionManager(const CollisionManager&) = delete;
		CollisionManager(CollisionManager&&) = delete;
		CollisionManager& operator=(const CollisionManager&) = delete;
		CollisionManager& operator=(CollisionManager&&) = delete;
		static std::pair<bool, glm::vec2> checkCollision(const std::vector<std::unique_ptr<Collider>>& firstColliders,
								   const glm::vec2& firstPosition,
								   const std::vector<std::unique_ptr<Collider>>& secondColliders,
								   const glm::vec2& secondPosition);
		static void handleCollision(std::shared_ptr<GameObject> first, std::shared_ptr<GameObject> second, const glm::vec2& collisionPoint);
		static glm::vec2 getCollisionLocation(const AABBCollider& first,
											  const glm::vec2& firstPosition,
											  const AABBCollider& second,
											  const glm::vec2& secondPosition);

	private:
		static bool checkCollisionAABB_AABB(const AABBCollider& first,
											const glm::vec2& firstPosition,
											const AABBCollider& second,
											const glm::vec2& secondPosition);

	};
}