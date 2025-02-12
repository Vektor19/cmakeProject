#pragma once
#include <glm/vec2.hpp>
#include "../../physics/collision/ICollidable.h"
class GameObject : public physics::ICollidable
{
public:
	GameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual void render() const = 0;
	virtual void update(const double delta) = 0;
	virtual ~GameObject();
	virtual glm::vec2& getCurrentPosition() { return m_position; }
	virtual glm::vec2& getCurrentDirection() { return m_direction; }
	virtual const glm::vec2& getSize() { return m_size;}
	virtual double getCurrentVelocity() { return m_velocity; }
	virtual void setVelocity(const double velocity);
protected:
	glm::vec2 m_position;
	glm::vec2 m_size;
	float m_rotation;
	float m_layer;

	glm::vec2 m_direction;
	double m_velocity;
};