#pragma once
#include "Collider.h"
#include <glm/vec2.hpp>
#include <vector>
#include <memory>
namespace physics
{
	class ICollidable
	{
	public:
		virtual const std::vector<std::unique_ptr<Collider>>& getColliders() const { return m_colliders; }
		virtual ~ICollidable() = 0;
	protected:
		std::vector<std::unique_ptr<Collider>> m_colliders;
	};
}