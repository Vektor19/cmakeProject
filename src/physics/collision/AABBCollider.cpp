#include "AABBCollider.h"

namespace physics
{
	AABBCollider::AABBCollider(CollisionLayer collisionLayer, int collisionMask, const glm::vec2& bottomLeft, const glm::vec2& topRight)
	: Collider(collisionLayer, collisionMask, ColliderType::AABB), m_bottomLeft(bottomLeft), m_topRight(topRight)
	{
	}
	AABBCollider::~AABBCollider()
	{
	}
}