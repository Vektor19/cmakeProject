#pragma once
#include <memory>
#include <array>
#include <vector>
#include <string>
class GameObject;
class Level
{
public:
	Level(const std::vector<std::string>& levelDescription);
	void render() const;
	void update(const uint64_t delta);
	~Level();

private:
	size_t m_widthBlocks;
	size_t m_heightBlocks;
	std::vector<std::shared_ptr<GameObject>> m_mapObjects;
};