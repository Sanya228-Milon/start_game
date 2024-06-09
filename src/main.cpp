#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

int WindowSizeX = 640; 
int WindowSizeY = 480; 


void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    WindowSizeX = width; 
    WindowSizeY = height; 
    glViewport(0, 0, WindowSizeX, WindowSizeY);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}


int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "Error with GLFW!" << std::endl; 
        return -1;
    }
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(WindowSizeX, WindowSizeY, "Start game!", nullptr, nullptr);
    if (!pWindow)
    {
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback); 

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

	if (!gladLoadGL()) 
	{
		std::cout << "Lol, error" << std::endl; 
		return -1; 
	} 
    std::cout << "Renderer - " << glGetString(GL_RENDERER) << std::endl; 
    std::cout << "OpenGL Version - " << glGetString(GL_VERSION) << std::endl;

	glClearColor(0, 1, 0, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}