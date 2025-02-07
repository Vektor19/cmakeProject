#include "Eagle.h"
#include "../../renderer/Sprite.h"
#include "../../resources/ResourceManager.h"

Eagle::Eagle(const glm::vec2& position,
	const glm::vec2& size,
	const float rotation)
	: GameObject(position, size, rotation)
	, m_eCurrentEagleState(EEagleState::Alive)
{
	m_sprites[static_cast<size_t>(EEagleState::Alive)] = resources::ResourcesManager::getSprite("eagle");
	m_sprites[static_cast<size_t>(EEagleState::Dead)]  = resources::ResourcesManager::getSprite("eagle_dead");
}

void Eagle::render() const
{
	m_sprites[static_cast<size_t>(m_eCurrentEagleState)]->render(m_position, m_size, m_rotation);
}

void Eagle::update(const uint64_t delta)
{
}
