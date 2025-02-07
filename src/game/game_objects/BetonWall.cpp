#include "BetonWall.h"
#include "../../renderer/Sprite.h"
#include "../../resources/ResourceManager.h"

BetonWall::BetonWall(const EBetonWallType eBetonWallType,
	const glm::vec2& position,
	const glm::vec2& size,
	const float rotation,
	const float layer)
	: GameObject(position, size, rotation, layer)
	, m_eBrickStates{EBrickState::Destroyed,
					 EBrickState::Destroyed,
					 EBrickState::Destroyed,
					 EBrickState::Destroyed }
	, m_blockOffsets { glm::vec2(0, m_size.y / 2.f),
					   glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
					   glm::vec2(0, 0),
					   glm::vec2(m_size.x / 2.f, 0) }
{
	m_sprites[static_cast<size_t>(EBrickState::All)] = resources::ResourcesManager::getSprite("betonWall");
	switch (eBetonWallType)
	{
	case EBetonWallType::All:
		m_eBrickStates.fill(EBrickState::All);
		break;
	case EBetonWallType::Top:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopLeft)]	 = EBrickState::All;
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopRight)]	 = EBrickState::All;
		break;
	case EBetonWallType::Bottom:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomLeft)]  = EBrickState::All;
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		break;
	case EBetonWallType::Left:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopLeft)]	 = EBrickState::All;
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomLeft)]  = EBrickState::All;
		break;
	case EBetonWallType::Right:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopRight)]	 = EBrickState::All;
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		break;
	case EBetonWallType::TopLeft:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopLeft)]	 = EBrickState::All;
		break;
	case EBetonWallType::TopRight:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopRight)]	 = EBrickState::All;
		break;
	case EBetonWallType::BottomLeft:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomLeft)]	 = EBrickState::All;
		break;
	case EBetonWallType::BottomRight:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		break;
	default:
		break;
	}
}

void BetonWall::render() const
{
	renderBrick(EBrickLocation::TopLeft);
	renderBrick(EBrickLocation::TopRight);
	renderBrick(EBrickLocation::BottomLeft);
	renderBrick(EBrickLocation::BottomRight);
}

void BetonWall::update(const double delta)
{
}

void BetonWall::renderBrick(EBrickLocation eBrickLocation) const
{
	const EBrickState state = m_eBrickStates[static_cast<size_t>(eBrickLocation)];
	if (state != EBrickState::Destroyed)
	{
		m_sprites[static_cast<size_t>(state)]->render(m_position + m_blockOffsets[static_cast<size_t>(eBrickLocation)], m_size/2.f, m_rotation, m_layer);
	}
}
