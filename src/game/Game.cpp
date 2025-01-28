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
    auto pSpriteShaderProgram = ResourcesManager::loadShaders("SpriteShaderProgram", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
    if (!pSpriteShaderProgram)
    {
        std::cerr << "Can't create shader program\n";
        return true;
    }
    auto tex = ResourcesManager::loadTexture("DefaultTexture", "res/textures/map_8x8.png");
    std::vector<std::string> subTexureNames =
    {
        "block",
        "topLeftBlock",
        "topRightBlock",
        "topBlock",
        "bottomLeftBlock",
        "leftBlock",
        "bottomLeftAndTopRightBlock",
        "withoutBottomRightBlock",
        "bottomrightBlock",
        "bottomRightAndTopLeftBlock",
        "rightBlock",
        "withoutBottomLeftBlock",
        "bottomBlock",
        "withoutTopRightBlock",
        "withoutTopLeftBlock",
        "water1",
        "water2",
        "water3",
        "betonBlock",
        "grassBlock",
        "leadBlock",
        "roadBlock",
        "bulletTop",
        "bulletBottom",
        "bulletLeft",
        "bulletRight"
    };
    std::vector<std::string> tanksSubTexureNames =
    {
        "tankTop1",
        "tankTop2",
        "tankLeft1",
        "tankLeft2",
        "tankBottom1",
        "tankBottom2",
        "tankRight1",
        "tankRight2"
    };
    auto texture = ResourcesManager::loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_8x8.png", 8, 8, std::move(subTexureNames));
    auto tankTexture = ResourcesManager::loadTextureAtlas("TanksTextureAtlas", "res/textures/tanks.png", 16, 16, std::move(tanksSubTexureNames));

    auto pAnimatedSprite = ResourcesManager::loadAnimatedSprite("DefaultAnimatedSprite", "DefaultTextureAtlas", "SpriteShaderProgram", 100, 100, "block");
    pAnimatedSprite->setPosition(glm::vec2(300));
    std::vector<std::pair<std::string, uint64_t>> waterState;
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));
    pAnimatedSprite->addState("water", std::move(waterState));
    pAnimatedSprite->setState("water");

    auto pTankSprite = ResourcesManager::loadAnimatedSprite("YellowTankSprite", "TanksTextureAtlas", "SpriteShaderProgram", 100, 100, "tankTop1");

    pTankSprite->setPosition(glm::vec2(0));

    std::vector<std::pair<std::string, uint64_t>> tankTopState;
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("tankTop1", 200000000));
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("tankTop2", 200000000));
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
