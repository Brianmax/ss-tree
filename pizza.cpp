/*Computacion Grafica 2022-01*/
/*George Brian Maxi Ccapa*/
/*Teclas a presionar: L--> Lineas
                      P--> Puntos
                      H-->Hibrido (Lineas y puntos)
                      */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

using namespace std;
void processInput(GLFWwindow* window);
double generate(float points[2160], double angle);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "out vec4 vertexColor;\n"
                                 "void main()\n"
                                 "{\n"
                                    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                    "vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
                                 "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec4 ourColor;\n"
                                   "void main()\n"
                                   "{\n"
                                        "   FragColor = ourColor;\n"
                                        "}\n\0";

bool linea = false, punto = false, hibrido = false;
bool red = false, green = false, blue = false, magenta = false, cyan = false, amarillo = false;
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices1[2160] = {};
    float vertices2[2160] = {};
    float vertices3[2160] = {};
    float vertices4[2160] = {};
    float vertices5[2160] = {};
    float vertices6[2160] = {};
    float vertices7[2160] = {};
    float vertices8[2160] = {};
    double angle = 0;
    angle = generate(vertices1, angle);
    angle = generate(vertices2, angle);
    angle = generate(vertices3, angle);
    angle = generate(vertices4, angle);
    angle = generate(vertices5, angle);
    angle = generate(vertices6, angle);
    angle = generate(vertices7, angle);
    angle = generate(vertices8, angle);

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
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    unsigned int VBO3, VAO3;
    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);
    glBindVertexArray(VAO3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    unsigned int VBO4, VAO4;
    glGenVertexArrays(1, &VAO4);
    glGenBuffers(1, &VBO4);
    glBindVertexArray(VAO4);
    glBindBuffer(GL_ARRAY_BUFFER, VBO4);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    unsigned int VBO5, VAO5;
    glGenVertexArrays(1, &VAO5);
    glGenBuffers(1, &VBO5);
    glBindVertexArray(VAO5);
    glBindBuffer(GL_ARRAY_BUFFER, VBO5);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices5), vertices5, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    unsigned int VBO6, VAO6;
    glGenVertexArrays(1, &VAO6);
    glGenBuffers(1, &VBO6);
    glBindVertexArray(VAO6);
    glBindBuffer(GL_ARRAY_BUFFER, VBO6);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices6), vertices6, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    unsigned int VBO7, VAO7;
    glGenVertexArrays(1, &VAO7);
    glGenBuffers(1, &VBO7);
    glBindVertexArray(VAO7);
    glBindBuffer(GL_ARRAY_BUFFER, VBO7);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices7), vertices7, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    unsigned int VBO8, VAO8;
    glGenVertexArrays(1, &VAO8);
    glGenBuffers(1, &VBO8);
    glBindVertexArray(VAO8);
    glBindBuffer(GL_ARRAY_BUFFER, VBO8);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices8), vertices8, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    glPointSize(8);
    glLineWidth(5);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);


        glClearColor(0.8f, 0.5f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shaderProgram);
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
        if (punto) {

            glBindVertexArray(VAO1);
            glDrawArrays(GL_POINTS, 0, 2160);

            glBindVertexArray(VAO2);
            glDrawArrays(GL_POINTS, 0, 2160);

            glBindVertexArray(VAO3);
            glDrawArrays(GL_POINTS, 0, 2160);

            glBindVertexArray(VAO4);
            glDrawArrays(GL_POINTS, 0, 2160);

            glBindVertexArray(VAO5);
            glDrawArrays(GL_POINTS, 0, 2160);

            glBindVertexArray(VAO6);
            glDrawArrays(GL_POINTS, 0, 2160);

            glBindVertexArray(VAO7);
            glDrawArrays(GL_POINTS, 0, 2160);

            glBindVertexArray(VAO8);
            glDrawArrays(GL_POINTS, 0, 2160);
        }

        if (linea) {
            glBindVertexArray(VAO1);
            glDrawArrays(GL_LINES, 0, 2160);

            glBindVertexArray(VAO2);
            glDrawArrays(GL_LINES, 0, 2160);

            glBindVertexArray(VAO3);
            glDrawArrays(GL_LINES, 0, 2160);

            glBindVertexArray(VAO4);
            glDrawArrays(GL_LINES, 0, 2160);

            glBindVertexArray(VAO5);
            glDrawArrays(GL_LINES, 0, 2160);

            glBindVertexArray(VAO6);
            glDrawArrays(GL_LINES, 0, 2160);

            glBindVertexArray(VAO7);
            glDrawArrays(GL_LINES, 0, 2160);

            glBindVertexArray(VAO8);
            glDrawArrays(GL_LINES, 0, 2160);
        }

        if (hibrido) {

            glBindVertexArray(VAO1);
            glDrawArrays(GL_LINES, 0, 2160);

            glBindVertexArray(VAO2);
            glDrawArrays(GL_POINTS, 0, 2160);

            glBindVertexArray(VAO3);
            glDrawArrays(GL_LINES, 0, 2160);

            glBindVertexArray(VAO4);
            glDrawArrays(GL_POINTS, 0, 2160);

            glBindVertexArray(VAO5);
            glDrawArrays(GL_LINES, 0, 2160);

            glBindVertexArray(VAO6);
            glDrawArrays(GL_POINTS, 0, 2160);

            glBindVertexArray(VAO7);
            glDrawArrays(GL_LINES, 0, 2160);

            glBindVertexArray(VAO8);
            glDrawArrays(GL_POINTS, 0, 2160);
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
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

double generate(float vertices1[2160], double angle)
{

    for (int i = 0; i < 2160; i = i + 6)
    {
        vertices1[i] = 0; vertices1[i + 1] = 0; vertices1[i + 2] = 0;
        float ans1 = (-sinf(angle) * 0.6f);
        float ans2 = (-cosf(angle) * 0.6f);
        angle = angle + 0.00218;
        vertices1[i + 3] = ans1;
        vertices1[(i + 4)] = ans2;
        vertices1[(i + 5)] = 0.0f;
    }
    return angle;
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
    if (key == GLFW_KEY_H && action == GLFW_PRESS)
    {
        if (hibrido)
            hibrido = false;
        else
            hibrido = true;
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        if (punto)
            punto = false;
        else
            punto = true;
    }
}
