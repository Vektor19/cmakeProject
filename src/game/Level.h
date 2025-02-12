#pragma once
#include <memory>
#include <array>
#include <vector>
#include <string>
#include <glm/vec2.hpp>
class GameObject;
class Level
{
public:
	static constexpr unsigned int BLOCK_SIZE = 16;
	Level(const std::vector<std::string>& levelDescription);
	void render() const;
	void update(const double delta);
	size_t getLevelWidth() const;
	size_t getLevelHeight() const;
	const glm::ivec2& getPlayerRespawn1() const { return m_playerRespawn1; }
	const glm::ivec2& getPlayerRespawn2() const { return m_playerRespawn2; }
	const glm::ivec2& getEnemyRespawn1() const { return m_enemyRespawn1; }
	const glm::ivec2& getEnemyRespawn2() const { return m_enemyRespawn2; }
	const glm::ivec2& getEnemyRespawn3() const { return m_enemyRespawn3; }

	const std::vector<std::shared_ptr<GameObject>>& getMapObjects() const { return m_mapObjects; }
	std::vector<std::shared_ptr<GameObject>> getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight) const;
	~Level();

private:
	size_t m_widthBlocks;
	size_t m_heightBlocks;
	unsigned int m_widthPixels = 0;
	unsigned int m_heightPixels = 0;

	glm::ivec2 m_playerRespawn1;
	glm::ivec2 m_playerRespawn2;
	glm::ivec2 m_enemyRespawn1;
	glm::ivec2 m_enemyRespawn2;
	glm::ivec2 m_enemyRespawn3;
	std::vector<std::shared_ptr<GameObject>> m_mapObjects;
};