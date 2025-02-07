#pragma once
#include <array>

class Tank;
class Level;
class Game
{
public:
	Game(const glm::ivec2& windowSize);
	~Game();
	bool init();
	void update(const double delta);
	void render();
	void setKey(const int key, const int action);
	size_t getCurrentLevelWidth() const;
	size_t getCurrentLevelHeight() const;
private:
	std::array<bool,349> m_keys;
	enum class GameState
	{
		Active,
		Pause
	};
	glm::ivec2 m_windowSize;
	GameState m_eCurrentGameState;
	std::unique_ptr<Tank> m_pTank;
	std::unique_ptr<Level> m_pLevel;
};
