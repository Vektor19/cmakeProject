#include "Level.h"
#include "game_objects/GameObject.h"
#include "game_objects/BrickWall.h"
#include "game_objects/BetonWall.h"
#include "game_objects/Water.h"
#include "game_objects/Trees.h"
#include "game_objects/Ice.h"
#include "game_objects/Eagle.h"
#include "game_objects/Border.h"
#include "game_objects/Tank.h"
#include "../resources/ResourceManager.h"
#include "../physics/PhysicsEngine.h"
#include "DynamicObjectsRenderer.h"
#include <iostream>
#include <cmath>
#include <algorithm>


Level::Level(const std::vector<std::string>& levelDescription)
{
	if (levelDescription.empty())
	{
		std::cerr << "Empty level description?" << std::endl;
	}
	m_widthBlocks = levelDescription[0].length();
	m_heightBlocks = levelDescription.size();
	m_widthPixels = static_cast<unsigned int>(m_widthBlocks * BLOCK_SIZE);
	m_heightPixels = static_cast<unsigned int>(m_heightBlocks * BLOCK_SIZE);
	m_playerRespawn1 = { BLOCK_SIZE * (m_widthBlocks / 2 - 1), BLOCK_SIZE / 2 };
	m_playerRespawn2 = { BLOCK_SIZE * (m_widthBlocks / 2 + 3), BLOCK_SIZE / 2 };
	m_enemyRespawn1  = { BLOCK_SIZE,                           BLOCK_SIZE * m_heightBlocks - BLOCK_SIZE / 2 };
	m_enemyRespawn2  = { BLOCK_SIZE * (m_widthBlocks / 2 + 1), BLOCK_SIZE * m_heightBlocks - BLOCK_SIZE / 2 };
	m_enemyRespawn3  = { BLOCK_SIZE * m_widthBlocks,           BLOCK_SIZE * m_heightBlocks - BLOCK_SIZE / 2 };

	m_mapObjects.reserve(m_widthBlocks * m_heightBlocks + 4);
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
				//m_mapObjects.emplace_back(nullptr);
				break;
			case 'L':
				m_playerRespawn2 = { currentLeftOffset, currentBottomOffset };
				//m_mapObjects.emplace_back(nullptr);
				break;
			case 'M':
				m_enemyRespawn1 = { currentLeftOffset, currentBottomOffset };
				//m_mapObjects.emplace_back(nullptr);
				break;
			case 'N':
				m_enemyRespawn2 = { currentLeftOffset, currentBottomOffset };
				//m_mapObjects.emplace_back(nullptr);
				break;
			case 'O':
				m_enemyRespawn3 = { currentLeftOffset, currentBottomOffset };
				//m_mapObjects.emplace_back(nullptr);
				break;
			default:
				break;
			}
			m_mapObjects.emplace_back(createGameObjectByChar(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0));
			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}

	auto enemyTank1 = std::make_shared<Tank>(Tank::ETankType::DarkGreen3, 0.05, m_enemyRespawn1, glm::vec2(Level::BLOCK_SIZE), 0.f);
	physics::PhysicsEngine::addDynamicObject(enemyTank1);
	DynamicObjectsRenderer::addDynamicObject(enemyTank1);
	m_nonMapDynamicObjects.emplace_back(enemyTank1);
	auto enemyTank2 = std::make_shared<Tank>(Tank::ETankType::Red1, 0.03, m_enemyRespawn2, glm::vec2(Level::BLOCK_SIZE), 0.f);
	physics::PhysicsEngine::addDynamicObject(enemyTank2);
	DynamicObjectsRenderer::addDynamicObject(enemyTank2);
	m_nonMapDynamicObjects.emplace_back(enemyTank2);
	auto enemyTank3 = std::make_shared<Tank>(Tank::ETankType::White1, 0.07, m_enemyRespawn3, glm::vec2(Level::BLOCK_SIZE), 0.f);
	physics::PhysicsEngine::addDynamicObject(enemyTank3);
	DynamicObjectsRenderer::addDynamicObject(enemyTank3);
	m_nonMapDynamicObjects.emplace_back(enemyTank3);
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

void Level::update(const double delta)
{
	for (const auto& gameObject : m_mapObjects)
	{
		if (gameObject)
		{
			gameObject->update(delta);
		}
	}
	for (const auto& gameObject : m_nonMapDynamicObjects)
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

std::vector<std::shared_ptr<GameObject>> Level::getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight) const
{
	/*std::cout << "New Pos: x: " << bottomLeft.x << " y: " << bottomLeft.y << std::endl;
	std::cout << "Top right Pos: x: " << topRight.x << " y: " << topRight.y << std::endl;*/

	std::vector<std::shared_ptr<GameObject>> objectsInArea;

	objectsInArea.reserve(9);
	glm::vec2 bottomLeft_converted(std::clamp(bottomLeft.x - BLOCK_SIZE, 0.f, static_cast<float>(m_widthPixels)),
		std::clamp(m_heightPixels - bottomLeft.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_heightPixels)));
	glm::vec2 topRight_converted(std::clamp(topRight.x - BLOCK_SIZE, 0.f, static_cast<float>(m_widthPixels)),
		std::clamp(m_heightPixels - topRight.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_heightPixels)));


	/*std::cout << "bottomLeft_converted.x: " << bottomLeft_converted.x << " bottomLeft_converted.y: " << bottomLeft_converted.y << std::endl;
	std::cout << "topRight_converted.x: " << topRight_converted.x << " topRight_converted.y: " << topRight_converted.y << std::endl;*/

	size_t startX = static_cast<size_t>(floor(bottomLeft_converted.x / BLOCK_SIZE));
	size_t endX = static_cast<size_t>(ceil(topRight_converted.x / BLOCK_SIZE));
	size_t startY = static_cast<size_t>(floor(topRight_converted.y / BLOCK_SIZE));
	size_t endY = static_cast<size_t>(ceil(bottomLeft_converted.y / BLOCK_SIZE));

	/*std::cout << "Start X: " << startX << ", End X: " << endX << std::endl;
	std::cout << "Start Y: " << startY << ", End Y: " << endY << std::endl;*/
	
	for (size_t currentColumn = startX; currentColumn < endX; ++currentColumn)
	{
		for (size_t currentRow = startY; currentRow < endY; ++currentRow)
		{
			auto& currentObject = m_mapObjects[currentRow * m_widthBlocks + currentColumn];
			if (currentObject)
			{
				objectsInArea.push_back(currentObject);
			}
		}
	}

	if (endX >= m_widthBlocks)
	{
		objectsInArea.push_back(m_mapObjects[m_mapObjects.size() - 1]);
	}
	if (startX <= 1)
	{
		objectsInArea.push_back(m_mapObjects[m_mapObjects.size() - 2]);
	}
	if (startY <= 1)
	{
		objectsInArea.push_back(m_mapObjects[m_mapObjects.size() - 3]);
	}
	if (endY >= m_heightBlocks)
	{
		objectsInArea.push_back(m_mapObjects[m_mapObjects.size() - 4]);
	}
	return objectsInArea;
}

void Level::replaceObject(std::shared_ptr<GameObject> oldObject, std::shared_ptr<GameObject> newObject)
{
	auto it = std::find(m_mapObjects.begin(), m_mapObjects.end(), oldObject);
	if (it != m_mapObjects.end())
	{
		*it = std::move(newObject);
	}
}

void Level::removeNonMapObject(std::shared_ptr<GameObject> object)
{
	auto it = std::find(m_nonMapDynamicObjects.begin(), m_nonMapDynamicObjects.end(), object);
	if (it != m_nonMapDynamicObjects.end())
	{
		m_nonMapDynamicObjects.erase(it);
	}
}

void Level::postInit(std::shared_ptr<Tank> pTank)
{
	for (const auto& obj : m_mapObjects) {
		if (auto ice = std::dynamic_pointer_cast<Ice>(obj)) {
			ice->setParentLevel(shared_from_this());
		}
	}
	for (const auto& obj : m_nonMapDynamicObjects) {
		if (auto tank = std::dynamic_pointer_cast<Tank>(obj)) {
			tank->setParentLevel(shared_from_this());
			tank->initAI(AIComponent::EActionType::Patrol);
			tank->setTarget(pTank);
		}
	}
}

Level::~Level()
{
}

std::shared_ptr<GameObject> Level::createGameObjectByChar(const char character, const glm::vec2& position, const glm::vec2& size, const float rotation)
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
