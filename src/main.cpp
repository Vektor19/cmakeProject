#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer/ShaderProgram.h"
#include "resources/ResourceManager.h"
int main(int argc, char** argv)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "vetal loh", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	
	if (!gladLoadGL())
	{
		std::cout<<"Can't load GLAD"<< std::endl;
		return -1;
	}
	std::cout<<"OpenGL "<<GLVersion.major<<"."<<GLVersion.minor<<std::endl;
    glfwSwapInterval(1);



    GLfloat points[] = {
        0.0f, 0.5f, 0.0f,
       -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
    };
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };


    
    resources::ResourcesManager* pResourcesManager = resources::ResourcesManager::get_instance();
    pResourcesManager->setExecutablePath(argv[0]);
    auto pDefaultShaderProgram = pResourcesManager->loadShaders("DefaultShaderProgram", "res/shaders/vertex_default.txt", "res/shaders/fragment_default.txt");
    if (!pDefaultShaderProgram)
    {
        std::cerr << "Can't create shader program\n";
        return -1;
    }

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    float angle = 0;
    /* Loop until the user closes the window */
	glClearColor(1,1,0,1);
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        pDefaultShaderProgram->use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    pResourcesManager->destroy();
    glfwTerminate();
    return 0;
}