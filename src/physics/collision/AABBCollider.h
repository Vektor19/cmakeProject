#pragma once
#include "Collider.h"
namespace physics
{
	class AABBCollider: public Collider
	{
	public:
		AABBCollider(CollisionLayer collisionLayer, int collisionMask);
		const glm::vec2& getBottomLeft() const { return m_bottomLeft; }
		const glm::vec2& getTopRight() const { return m_topRight; }
	private:
		glm::vec2 m_bottomLeft;
		glm::vec2 m_topRight;
	};
}