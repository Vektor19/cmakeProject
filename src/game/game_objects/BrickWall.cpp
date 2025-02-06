#include "BrickWall.h"
#include "../../renderer/Sprite.h"
#include "../../resources/ResourceManager.h"

BrickWall::BrickWall(const EBrickWallType eBrickWallType,
	const glm::vec2& position,
	const glm::vec2& size,
	const float rotation)
	: GameObject(position, size, rotation)
	, m_eBrickStates{EBrickState::Destroyed,
					 EBrickState::Destroyed,
					 EBrickState::Destroyed,
					 EBrickState::Destroyed }
{
	m_sprites[static_cast<size_t>(EBrickState::All)]				 = resources::ResourcesManager::getSprite("brickWall_All");
	m_sprites[static_cast<size_t>(EBrickState::TopLeft)]			 = resources::ResourcesManager::getSprite("brickWall_TopLeft");
	m_sprites[static_cast<size_t>(EBrickState::TopRight)]			 = resources::ResourcesManager::getSprite("brickWall_TopRight");
	m_sprites[static_cast<size_t>(EBrickState::Top)]				 = resources::ResourcesManager::getSprite("brickWall_Top");
	m_sprites[static_cast<size_t>(EBrickState::BottomLeft)]			 = resources::ResourcesManager::getSprite("brickWall_BottomLeft");
	m_sprites[static_cast<size_t>(EBrickState::Left)]	             = resources::ResourcesManager::getSprite("brickWall_Left");
	m_sprites[static_cast<size_t>(EBrickState::TopRight_BottomLeft)] = resources::ResourcesManager::getSprite("brickWall_TopRight_BottomLeft");
	m_sprites[static_cast<size_t>(EBrickState::Top_BottomLeft)]      = resources::ResourcesManager::getSprite("brickWall_Top_BottomLeft");
	m_sprites[static_cast<size_t>(EBrickState::BottomRight)]         = resources::ResourcesManager::getSprite("brickWall_BottomRight");
	m_sprites[static_cast<size_t>(EBrickState::TopLeft_BottomRight)] = resources::ResourcesManager::getSprite("brickWall_TopLeft_BottomRight");
	m_sprites[static_cast<size_t>(EBrickState::Right)]				 = resources::ResourcesManager::getSprite("brickWall_Right");
	m_sprites[static_cast<size_t>(EBrickState::Top_BottomRight)]	 = resources::ResourcesManager::getSprite("brickWall_Top_BottomRight");
	m_sprites[static_cast<size_t>(EBrickState::Bottom)]				 = resources::ResourcesManager::getSprite("brickWall_Bottom");
	m_sprites[static_cast<size_t>(EBrickState::TopLeft_Bottom)]		 = resources::ResourcesManager::getSprite("brickWall_TopLeft_Bottom");
	m_sprites[static_cast<size_t>(EBrickState::TopRight_Bottom)]	 = resources::ResourcesManager::getSprite("brickWall_TopRight_Bottom");
	switch (eBrickWallType)
	{
	case EBrickWallType::All:
		m_eBrickStates.fill(EBrickState::All);
		break;
	case EBrickWallType::Top:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopLeft)]	 = EBrickState::All;
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopRight)]	 = EBrickState::All;
		break;
	case EBrickWallType::Bottom:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomLeft)]  = EBrickState::All;
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		break;
	case EBrickWallType::Left:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopLeft)]	 = EBrickState::All;
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomLeft)]  = EBrickState::All;
		break;
	case EBrickWallType::Right:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopRight)]	 = EBrickState::All;
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		break;
	case EBrickWallType::TopLeft:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopLeft)]	 = EBrickState::All;
		break;
	case EBrickWallType::TopRight:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::TopRight)]	 = EBrickState::All;
		break;
	case EBrickWallType::BottomLeft:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomLeft)]	 = EBrickState::All;
		break;
	case EBrickWallType::BottomRight:
		m_eBrickStates[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		break;
	default:
		break;
	}
}

void BrickWall::render() const
{
	renderBrick(EBrickLocation::TopLeft);
	renderBrick(EBrickLocation::TopRight);
	renderBrick(EBrickLocation::BottomLeft);
	renderBrick(EBrickLocation::BottomRight);
}

void BrickWall::update(const uint64_t delta)
{
}

void BrickWall::renderBrick(EBrickLocation eBrickLocation) const
{
	static const std::array<glm::vec2, 4> offsets = { glm::vec2(0, m_size.y / 2.f),
													  glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
													  glm::vec2(0, 0),
													  glm::vec2(m_size.x / 2.f, 0) };
	const EBrickState state = m_eBrickStates[static_cast<size_t>(eBrickLocation)];
	if (state != EBrickState::Destroyed)
	{
		m_sprites[static_cast<size_t>(state)]->render(m_position + offsets[static_cast<size_t>(eBrickLocation)], m_size/4.f, m_rotation);
	}
}
