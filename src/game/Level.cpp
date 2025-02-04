#include "Level.h"
#include "game_objects/GameObject.h"
#include "game_objects/BrickWall.h"
#include "../resources/ResourceManager.h"
#include <iostream>
const unsigned int BLOCK_SIZE = 16;

std::shared_ptr<GameObject> createGameObjectByChar(const char character, const glm::vec2& position, const glm::vec2& size, const float rotation = 0)
{
	switch (character)
	{
	case '0':
		return std::make_shared<BrickWall>(resources::ResourcesManager::getSprite("brickWall_Right"), position, size, rotation);
	case '1':
		return std::make_shared<BrickWall>(resources::ResourcesManager::getSprite("brickWall_Bottom"), position, size, rotation);
	case '2':
		return std::make_shared<BrickWall>(resources::ResourcesManager::getSprite("brickWall_Left"), position, size, rotation);
	case '3':
		return std::make_shared<BrickWall>(resources::ResourcesManager::getSprite("brickWall_Top"), position, size, rotation);
	case '4':
		return std::make_shared<BrickWall>(resources::ResourcesManager::getSprite("brickWall_All"), position, size, rotation);
	case 'G':
		return std::make_shared<BrickWall>(resources::ResourcesManager::getSprite("brickWall_BottomLeft"), position, size, rotation);
	case 'H':
		return std::make_shared<BrickWall>(resources::ResourcesManager::getSprite("brickWall_BottomRight"), position, size, rotation);
	case 'I':
		return std::make_shared<BrickWall>(resources::ResourcesManager::getSprite("brickWall_TopLeft"), position, size, rotation);
	case 'J':
		return std::make_shared<BrickWall>(resources::ResourcesManager::getSprite("brickWall_TopRight"), position, size, rotation);
	case 'D':
		return nullptr;
	default:
		std::cerr << "Unknown character: " << character << std::endl;
	}
	return nullptr;
}
Level::Level(const std::vector<std::string>& levelDescription)
{
	if (levelDescription.empty())
	{
		std::cerr << "Empty level description?" << std::endl;
	}
	m_widthBlocks = levelDescription[0].length();
	m_heightBlocks = levelDescription.size();
	m_mapObjects.reserve(static_cast<size_t>(m_widthBlocks) * m_heightBlocks);
	unsigned int currentBottomOffset = static_cast<unsigned int>(BLOCK_SIZE * (m_heightBlocks - 1));
	for (const std::string& currentRow : levelDescription)
	{
		unsigned int currentLeftOffset = 0;
		for (const char currentElement : currentRow)
		{
			m_mapObjects.emplace_back(createGameObjectByChar(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0));
			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}
}

void Level::render() const
{
	for (const auto& gameObject: m_mapObjects)
	{
		if (gameObject)
		{
			gameObject->render();
		}
	}
}

void Level::update(const uint64_t delta)
{
	for (const auto& gameObject : m_mapObjects)
	{
		if (gameObject)
		{
			gameObject->update(delta);
		}
	}
}

Level::~Level()
{
}
