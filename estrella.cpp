/*Computacion Grafica 2022-01*/
/*George Brian Maxi Ccapa
Teclas: S--> LINE_STRIP
        P--> PUNTOS
        L--> LINEA SIMPLE
        T--> TRIANGUOS
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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

    unsigned int shaderProgram;
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

    unsigned int VBO5, VAO5;
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
        processInput(window);

        glClearColor(0.8f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            glBindVertexArray(VAO1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glBindVertexArray(VAO2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glBindVertexArray(VAO3);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            glBindVertexArray(VAO4);
            glDrawArrays(GL_LINE_LOOP, 0, 10);
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            glBindVertexArray(VAO5);
            glDrawArrays(GL_LINE_STRIP, 0, 11);
        }

        if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
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
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
