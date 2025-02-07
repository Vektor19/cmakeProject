#include "Border.h"
#include "../../renderer/Sprite.h"
#include "../../resources/ResourceManager.h"

Border::Border(const glm::vec2& position,
	const glm::vec2& size,
	const float rotation,
	const float layer)
	: GameObject(position, size, rotation, layer)
	, m_sprite(resources::ResourcesManager::getSprite("border"))
{
}

void Border::render() const
{
	m_sprite->render(m_position, m_size, m_rotation, m_layer);
}

void Border::update(const double delta)
{
}
