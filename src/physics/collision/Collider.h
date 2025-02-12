#pragma once
#include <glm/vec2.hpp>
namespace physics
{
	class Collider
	{
	public:
		enum class CollisionLayer {
			None = 0,
			Static = 1 << 0,
			Dynamic = 1 << 1,
			Water = 1 << 2,
			Bullet = 1 << 3,
		};
		enum class ColliderType {
			AABB = 0,
			Circle
		};
		Collider(CollisionLayer collisionLayer, int collisionMask, ColliderType type);
		virtual bool canCollideWith(const Collider& other) const;
		ColliderType getType() const { return m_type; }
		virtual ~Collider() = 0;
	protected:
		CollisionLayer m_layer;
		int m_collisionMask;
		ColliderType m_type;
	};
}