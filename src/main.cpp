#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <iostream>
#include "renderer/ShaderProgram.h"
#include "resources/ResourceManager.h"
#include "renderer/Texture2D.h"
#include "renderer/Sprite.h"
#include "renderer/Renderer.h"
#include "game/Game.h"
#include <chrono>

using namespace resources;

glm::ivec2 windowSize(13 * 16, 14 * 16);
std::unique_ptr<Game> g_pGame = std::make_unique<Game>(windowSize);

void glfwWindowSizeCallback(GLFWwindow* window, int newWidth, int newHeight)
{
    windowSize.x = newWidth;
    windowSize.y = newHeight;
    unsigned int viewPortWidth = newWidth;
    unsigned int viewPortHeight = newHeight;
    unsigned int viewPortLeftOffset = 0;
    unsigned int viewPortBottomOffset = 0;

    const float levelAspectRation = static_cast<float>(g_pGame->getCurrentLevelWidth()) / g_pGame->getCurrentLevelHeight();
    if (static_cast<float>(windowSize.x) / windowSize.y > levelAspectRation)
    {
        viewPortWidth = static_cast<unsigned int>(newHeight * levelAspectRation);
        viewPortLeftOffset = (newWidth - viewPortWidth) / 2;
    }
    else
    {
        viewPortHeight = static_cast<unsigned int>(newWidth / levelAspectRation);
        viewPortBottomOffset = (newHeight - viewPortHeight) / 2;
    }
    renderer::Renderer::setViewport(viewPortWidth, viewPortHeight, viewPortLeftOffset, viewPortBottomOffset);
}
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    g_pGame->setKey(key, action);
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
	std::cout<<"OpenGL "<< renderer::Renderer::getGlVersion()<<std::endl;
    glfwSwapInterval(1);
    renderer::Renderer::setClearColor(0, 0, 0, 1);
    renderer::Renderer::setDepthTest(true);
    ResourcesManager::setExecutablePath(argv[0]);
    if(!g_pGame->init())
    {
        std::cerr << "Can't init game";
        return -1;
    }
    glfwSetWindowSize(window, static_cast<int>(g_pGame->getCurrentLevelWidth()), static_cast<int>(g_pGame->getCurrentLevelHeight()));
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window))
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(currentTime - lastTime).count();
        lastTime = currentTime;
        g_pGame->update(duration);
        /* Render here */
        renderer::Renderer::clear();
        g_pGame->render();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    g_pGame = nullptr;
    glfwTerminate();
    return 0;
}