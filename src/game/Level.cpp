#include "Level.h"
#include "game_objects/GameObject.h"
#include <iostream>
const unsigned int BLOCK_SIZE = 16;
Level::Level(const std::vector<std::string>& levelDescription)
{
	if (levelDescription.empty())
	{
		std::cerr << "Empty level description?" << std::endl;
	}
	m_widthBlocks = levelDescription[0].length();
	m_heightBlocks = levelDescription.size();
	m_mapObjects.reserve(static_cast<size_t>(m_widthBlocks) * m_heightBlocks);
	unsigned int currentBottomOffset = BLOCK_SIZE * (m_heightBlocks - 1);
	for (const std::string& currentRow : levelDescription)
	{
		unsigned int currentLeftOffset = 0;
		for (const char currentElement : currentRow)
		{
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
