#include "../resources/ResourceManager.h"
#include "../renderer/ShaderProgram.h"
#include "../renderer/Texture2D.h"
#include "../renderer/Sprite.h"
#include "../physics/PhysicsEngine.h"
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Game.h"
#include "../game/game_objects/Tank.h"
#include "../game/Level.h"
#include <GLFW/glfw3.h>
using namespace resources;
Game::Game(const glm::ivec2& windowSize)
    : m_eCurrentGameState(GameState::Active)
    , m_windowSize(windowSize)
{
    m_keys.fill(false);
}

Game::~Game()
{
    ResourcesManager::unloadAllResources();
}

bool Game::init()
{
    ResourcesManager::loadJSONResources("res/resources.json");
    auto pSpriteShaderProgram = ResourcesManager::getShaderProgram("spriteShader");
    if (!pSpriteShaderProgram)
    {
        std::cerr << "No spriteShader!" << std::endl;
        return false;
    }
    auto pTanksTextureAtlas = ResourcesManager::getTexture("tanksTextureAtlas");
    if (!pTanksTextureAtlas)
    {
        std::cerr << "No tanksTextureAtlas!" << std::endl;
        return false;
    }

    m_pLevel = std::make_shared<Level>(ResourcesManager::getLevelsDescriptions()[1]);
    m_windowSize.x = static_cast<int>(m_pLevel->getLevelWidth());
    m_windowSize.y = static_cast<int>(m_pLevel->getLevelHeight());
    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);
    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix("projectionMat", projectionMatrix);
    
    m_pTank = std::make_shared<Tank>(Tank::ETankType::Yellow1, 0.05, m_pLevel->getPlayerRespawn1(), glm::vec2(Level::BLOCK_SIZE), 0.f);
    physics::PhysicsEngine::addDynamicObject(m_pTank);
    physics::PhysicsEngine::setCurrentLevel(m_pLevel);
    return true;
}

void Game::update(const double delta)
{
    //ResourcesManager::getAnimatedSprite("DefaultAnimatedSprite")->update(delta);
    if (m_pTank)
    {
        if (m_keys[GLFW_KEY_W])
        {
            m_pTank->setOrientation(Tank::EOrientation::Top);
            m_pTank->setVelocity(m_pTank->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_A])
        {
            m_pTank->setOrientation(Tank::EOrientation::Left);
            m_pTank->setVelocity(m_pTank->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_S])
        {
            m_pTank->setOrientation(Tank::EOrientation::Bottom);
            m_pTank->setVelocity(m_pTank->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_D])
        {
            m_pTank->setOrientation(Tank::EOrientation::Right);
            m_pTank->setVelocity(m_pTank->getMaxVelocity());
        }
        else
        {
            m_pTank->setVelocity(0);
        }
        m_pTank->update(delta);
    }
    if (m_pLevel)
    {
        m_pLevel->update(delta);
    }
}

void Game::render()
{
    //ResourcesManager::getAnimatedSprite("DefaultAnimatedSprite")->render();
    if (m_pTank)
    {
        m_pTank->render();
    }
    if (m_pLevel)
    {
        m_pLevel->render();
    }
}

void Game::setKey(const int key, const int action)
{
	m_keys[key] = action;
}

size_t Game::getCurrentLevelWidth() const
{
    return m_pLevel->getLevelWidth();
}

size_t Game::getCurrentLevelHeight() const
{
    return m_pLevel->getLevelHeight();
}
