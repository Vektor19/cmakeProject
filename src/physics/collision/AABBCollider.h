#pragma once
#include "Collider.h"
namespace physics
{
	class AABBCollider: public Collider
	{
	public:
		AABBCollider(CollisionLayer collisionLayer, int collisionMask);
		struct AABB {
			glm::vec2 leftBottom;
			glm::vec2 topRight;
		};
	private:

	};
}