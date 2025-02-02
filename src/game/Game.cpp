#include "../resources/ResourceManager.h"
#include "../renderer/ShaderProgram.h"
#include "../renderer/Texture2D.h"
#include "../renderer/Sprite.h"
#include "../renderer/AnimatedSprite.h"
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Game.h"
#include "../game/Tank.h"
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
    auto pTankSprite = ResourcesManager::loadAnimatedSprite("YellowTankSprite", "tanksTextureAtlas", "spriteShader", 100, 100, "yellowType1_Top1");

    pTankSprite->setPosition(glm::vec2(0));

    std::vector<std::pair<std::string, uint64_t>> tankTopState;
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("yellowType1_Top1", 200000000));
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("yellowType1_Top2", 200000000));
    pTankSprite->addState("TankTopState", std::move(tankTopState));
    pTankSprite->setState("TankTopState");

    std::vector<std::pair<std::string, uint64_t>> tankLeftState;
    tankLeftState.emplace_back(std::make_pair<std::string, uint64_t>("tankLeft1", 200000000));
    tankLeftState.emplace_back(std::make_pair<std::string, uint64_t>("tankLeft2", 200000000));
    pTankSprite->addState("TankLeftState", std::move(tankLeftState));

    std::vector<std::pair<std::string, uint64_t>> tankBottomState;
    tankBottomState.emplace_back(std::make_pair<std::string, uint64_t>("tankBottom1", 200000000));
    tankBottomState.emplace_back(std::make_pair<std::string, uint64_t>("tankBottom2", 200000000));
    pTankSprite->addState("TankBottomState", std::move(tankBottomState));

    std::vector<std::pair<std::string, uint64_t>> tankRightState;
    tankRightState.emplace_back(std::make_pair<std::string, uint64_t>("tankRight1", 200000000));
    tankRightState.emplace_back(std::make_pair<std::string, uint64_t>("tankRight2", 200000000));
    pTankSprite->addState("TankRightState", std::move(tankRightState));


    glm::mat4 modelMatrix = glm::mat4(1.f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(100.f, 200.f, 0.f));
    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);
    /* Loop until the user closes the window */
    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix("projectionMat", projectionMatrix);

    m_pTank = std::make_unique<Tank>(pTankSprite, 0.0000005, glm::vec2(0));

	return true;
}

void Game::update(const uint64_t delta)
{
    //ResourcesManager::getAnimatedSprite("DefaultAnimatedSprite")->update(delta);
    if (m_pTank)
    {
        m_pTank->update(delta);
    }
}

void Game::render()
{
    //ResourcesManager::getAnimatedSprite("DefaultAnimatedSprite")->render();
    if (m_pTank)
    {
        if (m_keys[GLFW_KEY_W])
        {
            m_pTank->setOrientation(Tank::EOrientation::Top);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_A])
        {
            m_pTank->setOrientation(Tank::EOrientation::Left);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_S])
        {
            m_pTank->setOrientation(Tank::EOrientation::Bottom);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_D])
        {
            m_pTank->setOrientation(Tank::EOrientation::Right);
            m_pTank->move(true);
        }
        else
        {
            m_pTank->move(false);
        }
        m_pTank->render();
    }
}

void Game::setKey(const int key, const int action)
{
	m_keys[key] = action;
}
