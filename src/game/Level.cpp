#include "Level.h"
#include "game_objects/GameObject.h"
#include "game_objects/BrickWall.h"
#include "game_objects/BetonWall.h"
#include "game_objects/Water.h"
#include "game_objects/Trees.h"
#include "game_objects/Ice.h"
#include "game_objects/Eagle.h"
#include "game_objects/Border.h"
#include "../resources/ResourceManager.h"
#include <iostream>

std::shared_ptr<GameObject> createGameObjectByChar(const char character, const glm::vec2& position, const glm::vec2& size, const float rotation = 0)
{
	switch (character)
	{
	case '0':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Right, position, size, rotation, 0.f);
	case '1':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Bottom, position, size, rotation, 0.f);
	case '2':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Left, position, size, rotation, 0.f);
	case '3':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Top, position, size, rotation, 0.f);
	case '4':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::All, position, size, rotation, 0.f);
	case 'G':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomLeft, position, size, rotation, 0.f);
	case 'H':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomRight, position, size, rotation, 0.f);
	case 'I':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopLeft, position, size, rotation, 0.f);
	case 'J':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopRight, position, size, rotation, 0.f);
	case '5':
		return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Right, position, size, rotation, 0.f);
	case '6':
		return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Bottom, position, size, rotation, 0.f);
	case '7':
		return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Left, position, size, rotation, 0.f);
	case '8':
		return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Top, position, size, rotation, 0.f);
	case '9':
		return std::make_shared<BetonWall>(BetonWall::EBetonWallType::All, position, size, rotation, 0.f);
	case 'A':
		return std::make_shared<Water>(position, size, rotation, 0.f);
	case 'B':
		return std::make_shared<Trees>(position, size, rotation, 1.f);
	case 'C':
		return std::make_shared<Ice>(position, size, rotation, -1.f);
	case 'E':
		return std::make_shared<Eagle>(position, size, rotation, 0.f);
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
	m_playerRespawn1 = { BLOCK_SIZE * (m_widthBlocks / 2 - 1), BLOCK_SIZE / 2 };
	m_playerRespawn2 = { BLOCK_SIZE * (m_widthBlocks / 2 + 3), BLOCK_SIZE / 2 };
	m_enemyRespawn1  = { BLOCK_SIZE,                           BLOCK_SIZE * m_heightBlocks - BLOCK_SIZE / 2 };
	m_enemyRespawn2  = { BLOCK_SIZE * (m_widthBlocks / 2 + 1), BLOCK_SIZE * m_heightBlocks - BLOCK_SIZE / 2 };
	m_enemyRespawn3  = { BLOCK_SIZE * m_widthBlocks,           BLOCK_SIZE * m_heightBlocks - BLOCK_SIZE / 2 };

	m_mapObjects.reserve(static_cast<size_t>(m_widthBlocks) * m_heightBlocks);
	unsigned int currentBottomOffset = static_cast<unsigned int>(BLOCK_SIZE * (m_heightBlocks - 1) + BLOCK_SIZE / 2.f);
	for (const std::string& currentRow : levelDescription)
	{
		unsigned int currentLeftOffset = BLOCK_SIZE;
		for (const char currentElement : currentRow)
		{
			switch (currentElement)
			{
			case 'K':
				m_playerRespawn1 = { currentLeftOffset, currentBottomOffset };
				break;
			case 'L':
				m_playerRespawn2 = { currentLeftOffset, currentBottomOffset };
				break;
			case 'M':
				m_enemyRespawn1 = { currentLeftOffset, currentBottomOffset };
				break;
			case 'N':
				m_enemyRespawn2 = { currentLeftOffset, currentBottomOffset };
				break;
			case 'O':
				m_enemyRespawn3 = { currentLeftOffset, currentBottomOffset };
				break;
			default:
				break;
			}
			m_mapObjects.emplace_back(createGameObjectByChar(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0));
			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}
	
	m_mapObjects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, 0.f), glm::vec2(m_widthBlocks * BLOCK_SIZE, BLOCK_SIZE / 2.f), 0, 0.f)); //bottom
	m_mapObjects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, m_heightBlocks * BLOCK_SIZE + BLOCK_SIZE / 2.f), glm::vec2(m_widthBlocks * BLOCK_SIZE, BLOCK_SIZE), 0, 0.f)); //top
	m_mapObjects.emplace_back(std::make_shared<Border>(glm::vec2(0.f, 0.f), glm::vec2(BLOCK_SIZE, (m_heightBlocks + 1) * BLOCK_SIZE), 0, 0.f)); //left
	m_mapObjects.emplace_back(std::make_shared<Border>(glm::vec2((m_widthBlocks + 1) * BLOCK_SIZE, 0.f), glm::vec2(BLOCK_SIZE * 2.f, (m_heightBlocks + 1) * BLOCK_SIZE), 0, 0.f)); //right
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

size_t Level::getLevelWidth() const
{
	return (m_widthBlocks + 3) * BLOCK_SIZE;
}

size_t Level::getLevelHeight() const
{
	return (m_heightBlocks + 1) * BLOCK_SIZE;
}

Level::~Level()
{
}
