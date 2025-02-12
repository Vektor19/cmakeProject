#include "AABBCollider.h"

namespace physics
{
	AABBCollider::AABBCollider(CollisionLayer collisionLayer, int collisionMask) : Collider(collisionLayer, collisionMask, ColliderType::AABB)
	{
	}
}