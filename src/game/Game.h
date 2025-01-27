#pragma once
#include <array>
class Game
{
public:
	Game(const glm::ivec2& windowSize);
	~Game();
	bool init();
	void update(const uint64_t delta);
	void render();
	void setKey(const int key, const int action);
private:
	std::array<bool,349> m_keys;
	enum class GameState
	{
		Active,
		Pause
	};
	glm::ivec2 m_windowSize;
	GameState m_eCurrentGameState;
};
