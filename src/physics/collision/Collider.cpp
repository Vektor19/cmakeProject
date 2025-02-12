#include "Collider.h"
namespace physics
{
	Collider::Collider(CollisionLayer collisionLayer, int collisionMask): m_layer(collisionLayer), m_collisionMask(collisionMask)
	{
	}
	bool Collider::canCollideWith(const Collider& other) const
	{
		return (m_collisionMask & static_cast<int>(other.m_layer)) != 0;
	}
}