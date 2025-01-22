#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "renderer/ShaderProgram.h"
#include "resources/ResourceManager.h"
#include "renderer/Texture2D.h"
#include "renderer/Sprite.h"
#include "renderer/AnimatedSprite.h"

glm::ivec2 windowSize(1280, 720);

void glfwWindowSizeCallback(GLFWwindow* window, int newWidth, int newHeight)
{
    windowSize.x = newWidth;
    windowSize.y = newHeight;
    glViewport(0, 0, windowSize.x, windowSize.y);
}
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
int main(int argc, char** argv)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowSize.x, windowSize.y, "vetal loh", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwMakeContextCurrent(window);
	
	if (!gladLoadGL())
	{
		std::cout<<"Can't load GLAD"<< std::endl;
		return -1;
	}
	std::cout<<"OpenGL "<<GLVersion.major<<"."<<GLVersion.minor<<std::endl;
    glfwSwapInterval(1);



    GLfloat points[] = {
        0.0f, 50.f, 0.0f,
       -50.0f, -50.0f, 0.0f,
        50.f, -50.0f, 0.0f,
    };
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };
    GLfloat texCoords[] = {
        0.5f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
    };


    
    resources::ResourcesManager* pResourcesManager = resources::ResourcesManager::get_instance();
    pResourcesManager->setExecutablePath(argv[0]);
    auto pDefaultShaderProgram = pResourcesManager->loadShaders("DefaultShaderProgram", "res/shaders/vertex_default.txt", "res/shaders/fragment_default.txt");
    if (!pDefaultShaderProgram)
    {
        std::cerr << "Can't create shader program\n";
        return -1;
    }
    auto pSpriteShaderProgram = pResourcesManager->loadShaders("SpriteShaderProgram", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
    if (!pSpriteShaderProgram)
    {
        std::cerr << "Can't create shader program\n";
        return -1;
    }
    auto tex = pResourcesManager->loadTexture("DefaultTexture", "res/textures/map_8x8.png");
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
    auto texture = pResourcesManager->loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_8x8.png", 8, 8, std::move(subTexureNames));
    auto pSprite = pResourcesManager->loadSprite("DefaultSprite", "DefaultTextureAtlas", "SpriteShaderProgram", 100, 100, "block");
    pSprite->setPosition(glm::vec2(100));

    auto pAnimatedSprite = pResourcesManager->loadAnimatedSprite("DefaultAnimatedSprite", "DefaultTextureAtlas", "SpriteShaderProgram", 100, 100, "block");
    pAnimatedSprite->setPosition(glm::vec2(300));
    std::vector<std::pair<std::string, uint64_t>> waterState;
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));

    std::vector<std::pair<std::string, uint64_t>> blockState;
    blockState.emplace_back(std::make_pair<std::string, uint64_t>("block", 1000000000));
    blockState.emplace_back(std::make_pair<std::string, uint64_t>("grassBlock", 1000000000));
    pAnimatedSprite->addState("water", std::move(waterState));
    pAnimatedSprite->addState("block", std::move(blockState));
    pAnimatedSprite->setState("water");
    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint tex_vbo = 0;
    glGenBuffers(1, &tex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    
    pDefaultShaderProgram->use();
    pDefaultShaderProgram->setInt("tex", 0);
    
    glm::mat4 modelMatrix = glm::mat4(1.f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(100.f, 200.f, 0.f));
    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(windowSize.x), 0.f, static_cast<float>(windowSize.y), -100.f, 100.f);
    /* Loop until the user closes the window */
    pDefaultShaderProgram->setMatrix("projectionMat", projectionMatrix);
    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setInt("tex", 0);
    pSpriteShaderProgram->setMatrix("projectionMat", projectionMatrix);
    glClearColor(1,1,0,1);
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window))
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
        lastTime = currentTime;
        pAnimatedSprite->update(duration);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        pSprite->render();
        pAnimatedSprite->render();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    pResourcesManager->destroy();
    glfwTerminate();
    return 0;
}