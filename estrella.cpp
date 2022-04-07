/*Computacion Grafica 2022-01*/
/*George Brian Maxi Ccapa
Teclas: S--> LINE_STRIP
        P--> PUNTOS
        L--> LINEA SIMPLE
        T--> TRIANGUOS
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "math.h"
#include <iostream>
#include <vector>
#include <array>
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mods);
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "out vec4 vertexColor;\n"
                                 "void main()\n"
                                 "{\n"
                                    "gl_Position = vec4(aPos, 1.0);\n"
                                    "vertexColor = vec4(0.0f, 0.0f, 0.5f, 1.0f);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec4 ourColor;;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = ourColor;\n"
                                   "}\0";


unsigned int VBO5, VAO5;
bool linea = false, punto = false, triangulo = false;
bool red = false, green = false, blue = false, magenta = false, cyan = false, amarillo = false;
unsigned int shaderProgram;
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    glfwSetKeyCallback(window, key_callback2);
    glfwSetKeyCallback(window, key_callback);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Compiling Vertex Shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    //Check Shader compiling
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Compile Fragment Shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    // Shader Program


    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices1[] = {
            0.3f,  -0.4f, 0.0f,
            -0.6f,  0.1f, 0.0f,
            0.112f,  0.1f, 0.0f
            };
    float vertices2[] = {
            -0.4f,  -0.4f, 0.0f,
            0.6f,  0.1f, 0.0f,
            -0.15f,  0.1f, 0.0f
    };
    float vertices3[] = {
            0.0f,  0.4f, 0.0f,
            0.112f,  0.1f, 0.0f,
            -0.15f,  0.1f, 0.0f
    };

    float vertices_lineas[] = {
            0.0f,  0.4f, 0.0f,
            0.112f,  0.1f, 0.0f,
            0.6f,  0.1f, 0.0f,
            0.189f,  -0.104f, 0.0f,
            0.3f,  -0.4f, 0.0f,
            -0.033f,  -0.215f, 0.0f,
            -0.4f,  -0.4f, 0.0f,
            -0.248,  -0.095f, 0.0f,
            -0.6f,  0.1f, 0.0f,
            -0.115f,  0.1f, 0.0f
    };
    float vertices_lineas_strip[] = {
            0.0f,  0.4f, 0.0f,
            0.112f,  0.1f, 0.0f,
            0.6f,  0.1f, 0.0f,
            0.189f,  -0.104f, 0.0f,
            0.3f,  -0.4f, 0.0f,
            -0.033f,  -0.215f, 0.0f,
            -0.4f,  -0.4f, 0.0f,
            -0.248,  -0.095f, 0.0f,
            -0.6f,  0.1f, 0.0f,
            -0.115f,  0.1f, 0.0f,
            0.0f,  0.4f, 0.0f
    };
    unsigned int VBO1, VAO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    unsigned int VBO2, VAO2;
    glGenBuffers(1, &VBO2);
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    unsigned int VBO3, VAO3;
    glGenBuffers(1, &VBO3);
    glGenVertexArrays(1, &VAO3);
    glBindVertexArray(VAO3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    unsigned int VBO4, VAO4;
    glGenBuffers(1, &VBO4);
    glGenVertexArrays(1, &VAO4);
    glBindVertexArray(VAO4);
    glBindBuffer(GL_ARRAY_BUFFER, VBO4);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_lineas), vertices_lineas, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    glGenBuffers(1, &VBO5);
    glGenVertexArrays(1, &VAO5);
    glBindVertexArray(VAO5);
    glBindBuffer(GL_ARRAY_BUFFER, VBO5);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_lineas_strip), vertices_lineas_strip, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glPointSize(8);
    glLineWidth(5);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.7f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        //Dibujo
        if (red)
        {
            float timeValue = glfwGetTime();
            float redValue = (sin(timeValue) / 2.0f) + 0.5f;
            int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
            glUseProgram(shaderProgram);
            glUniform4f(vertexColorLocation, redValue, 0.0f, 0.0f, 1.0f);
        }
        if (green)
        {
            float timeValue = glfwGetTime();
            float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
            int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
            glUseProgram(shaderProgram);
            glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        }
        if (blue)
        {
            float timeValue = glfwGetTime();
            float blueValue = (sin(timeValue) / 2.0f) + 0.5f;
            int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
            glUseProgram(shaderProgram);
            glUniform4f(vertexColorLocation, 0.0f, 0.0f, blueValue, 1.0f);
        }
        if (cyan)
        {
            float timeValue = glfwGetTime();
            float blueValue = (sin(timeValue) / 2.0f) + 0.5f;
            float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
            int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
            glUseProgram(shaderProgram);
            glUniform4f(vertexColorLocation, 0.0f, greenValue, blueValue, 1.0f);
        }
        if (amarillo)
        {
            float timeValue = glfwGetTime();
            float redValue = (sin(timeValue) / 2.0f) + 0.5f;
            float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
            int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
            glUseProgram(shaderProgram);
            glUniform4f(vertexColorLocation, redValue, greenValue, 0.0f, 1.0f);
        }
        if (magenta)
        {
            float timeValue = glfwGetTime();
            float redValue = (sin(timeValue) / 2.0f) + 0.5f;
            float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
            float blueValue = (sin(timeValue) / 2.0f) + 0.5f;
            int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
            glUseProgram(shaderProgram);
            glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
        }
        if(linea) {
            glBindVertexArray(VAO5);
            glDrawArrays(GL_LINE_STRIP, 0, 11);
        }
        if (triangulo) {
            glBindVertexArray(VAO1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glBindVertexArray(VAO2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glBindVertexArray(VAO3);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        if (punto) {
            glBindVertexArray(VAO5);
            glDrawArrays(GL_POINTS, 0, 11);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        if (red)
        {
            red = false;
        }
        else
            red = true;
    }
    if (key == GLFW_KEY_G && action == GLFW_PRESS)
    {
        if (green)
        {
            green = false;
        }
        else
            green = true;
    }
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
    {
        if (blue)
        {
            blue = false;
        }
        else
            blue = true;
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        if (cyan)
        {
            cyan = false;
        }
        else
            cyan = true;
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        if (amarillo)
        {
            amarillo = false;
        }
        else
            amarillo = true;
    }
    if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        if (magenta)
        {
            magenta = false;
        }
        else
            magenta = true;
    }

    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        if (linea)
            linea = false;
        else
            linea = true;
    }
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
    {
        if (triangulo)
            triangulo = false;
        else
            triangulo = true;
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        if (punto)
            punto = false;
        else
            punto = true;
    }
}
