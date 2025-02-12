#include "GameObject.h"

GameObject::GameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: m_position(position)
	, m_size(size)
	, m_rotation(rotation)
	, m_layer(layer)
	, m_direction(glm::vec2(0.f,1.f))
	, m_velocity(0)
{

}

GameObject::~GameObject()
{
}

void GameObject::setVelocity(const double velocity)
{
	m_velocity = velocity;
}
