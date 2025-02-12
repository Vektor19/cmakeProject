#pragma once
#include <unordered_set>
#include <memory>
#include "ICollidable.h"
#include "AABBCollider.h"
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
		static bool checkCollision(const std::vector<std::unique_ptr<Collider>>& firstColliders,
								   const glm::vec2& firstPosition,
								   const std::vector<std::unique_ptr<Collider>>& secondColliders,
								   const glm::vec2& secondPosition);

	private:
		static bool checkCollisionAABB_AABB(const AABBCollider& first,
											const glm::vec2& firstPosition,
											const AABBCollider& second,
											const glm::vec2& secondPosition);
	};
}