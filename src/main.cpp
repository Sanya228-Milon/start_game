#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

int WindowSizeX = 640; 
int WindowSizeY = 480; 

GLfloat point[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"}";


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

	glClearColor(0, 0, 0, 1);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, nullptr); 
    glCompileShader(vs); 

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, nullptr);
    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vs); 
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program); 

    glDeleteShader(vs); 
    glDeleteShader(fs);

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}