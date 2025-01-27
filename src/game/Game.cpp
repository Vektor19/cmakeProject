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
    auto pDefaultShaderProgram = ResourcesManager::loadShaders("DefaultShaderProgram", "res/shaders/vertex_default.txt", "res/shaders/fragment_default.txt");
    if (!pDefaultShaderProgram)
    {
        std::cerr << "Can't create shader program\n";
        return true;
    }
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
    auto texture = ResourcesManager::loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_8x8.png", 8, 8, std::move(subTexureNames));
    
    auto pAnimatedSprite = ResourcesManager::loadAnimatedSprite("DefaultAnimatedSprite", "DefaultTextureAtlas", "SpriteShaderProgram", 100, 100, "block");
    pAnimatedSprite->setPosition(glm::vec2(300));
    std::vector<std::pair<std::string, uint64_t>> waterState;
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));
    pAnimatedSprite->addState("water", std::move(waterState));
    pAnimatedSprite->setState("water");

    pDefaultShaderProgram->use();
    pDefaultShaderProgram->setInt("tex", 0);

    glm::mat4 modelMatrix = glm::mat4(1.f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(100.f, 200.f, 0.f));
    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);
    /* Loop until the user closes the window */
    pDefaultShaderProgram->setMatrix("projectionMat", projectionMatrix);
    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix("projectionMat", projectionMatrix);
	return true;
}

void Game::update(const uint64_t delta)
{
    ResourcesManager::getAnimatedSprite("DefaultAnimatedSprite")->update(delta);
}

void Game::render()
{
    ResourcesManager::getAnimatedSprite("DefaultAnimatedSprite")->render();
}

void Game::setKey(const int key, const int action)
{
	m_keys[key] = action;
}
