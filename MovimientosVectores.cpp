#include <iostream>
#include <random>
#include <math.h>
#include <time.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Variables for checking compilation/linking correctness
int success;
char infoLog[512];

// Basic vertex shader in GLSL (OpenGL Shading Language)
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

bool linea = false, punto = false, triangulo = false;
bool red = false, green = false, blue = false, magenta = false, cyan = false, amarillo = false;
int m = 0;

float up[3] = {0, 0.01, 0};
float down[3] = {0, -0.01, 0};
float left_[3] = {-0.01, 0, 0};
float right_[3] = {0.01, 0, 0};

struct vectorF
{
    float x, y, z = 0.0;
    vectorF(float x_, float y_)
    {
        x = x_;
        y = y_;
    }
    vectorF normalize(vectorF vector1, float norma);
    float normCalculate(vectorF vector1);
    void printVector();
};
void vectorF::printVector() {
    cout<< x << "   "<< y << "   "<< z << endl;
}
float vectorF::normCalculate(vectorF vector1) {
    return sqrt(pow(vector1.x,2) + pow(vector1.y,2) + pow(vector1.z,2));
}
vectorF vectorF::normalize(vectorF vector1, float norma) {
    if (norma == 1)
        return vector1;
    else
    {
        vector1.x = vector1.x/norma;
        vector1.y = vector1.y/norma;
        return vector1;
    }
}

bool checkColision(float *vertices)
{
    for (int i = 0; i < 9; i = i + 3)
    {
        if (vertices[i] >= 1.0 || vertices[i] <= -1.0 || vertices[i+1] >= 1.0 || vertices[i + 1] <= -1.0)
            return true;
    }
    return false;
}
void setVector(float *vertices, vectorF vector1)
{
    //vectorF vector1(0,0,0);
    //vector1 = generate();
    for (int i = 0; i < 9 ; i = i + 3){
        vertices[i] = vertices[i] + vector1.x;
        vertices[i + 1] = vertices[i + 1] + vector1.y;
    }
}
void restar(float *vertices, vectorF vector1)
{
    for (int i = 0; i < 9; i = i + 3)
    {
        vertices[i] = vertices[i] - vector1.x;
        vertices[i + 1] = vertices[i + 1] - vector1.y;
    }
}
void MovementHandler(float *vertices)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-1, 1);
    float v1 = dist(gen);
    float v2 = dist(gen);
    vectorF vector1(v1, v2);
    //vector1.printVector();
    //float norm = vector1.normCalculate(vector1);
    //vector1 = vector1.normalize(vector1, norm);
    //vector1.printVector();
    setVector(vertices, vector1);
    if (checkColision(vertices)){
        cout<<"Hola"<<endl;
        restar(vertices, vector1);
    }
}
void printArray(float *vertices)
{
    for (int i = 0; i < 9; i = i + 3)
        cout<<vertices[i] << "  "<< vertices[i+1]<<"  "<<vertices[i + 2] << endl;
}
int main() {
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 1. Build and compile our shader programs

    // Create a vertex shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Attach the shader source code to the shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    // Compile the vertex shader dynamically
    glCompileShader(vertexShader);

    // Check if compilation was successful
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
        std::cout << infoLog << std::endl;
    }

    // Create a fragment shader object
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Attach the shader source code to the shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    // Compile the fragment shader dynamically
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
        std::cout << infoLog << std::endl;
    }


    // 2. Link shaders

    // Create a shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Attach the compiled shaders to the shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check if linking was successful
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n";
        std::cout << infoLog << std::endl;
    }

    // Delete shader objects if we no longer need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // 3. Set up vertex data and configure vertex attributes

    // Define three vertices with 3D positions
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    // Generate vertex buffer object (VBO) and vertex array object (VAO)
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO, then bind VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy the vertex data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // Set attributes that describe how OpenGL should interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Unbind so other calls won't modify VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glPointSize(8);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        if (m == 1)
        {
            MovementHandler(vertices);
            //printArray(vertices);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // Set attributes that describe how OpenGL should interpret the vertex data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
            glEnableVertexAttribArray(0);
        }
        /*if (m == 1)
        {
            setVector(vertices, up);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // Set attributes that describe how OpenGL should interpret the vertex data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }
        if (m == 2)
        {
            setVector(vertices, down);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // Set attributes that describe how OpenGL should interpret the vertex data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }
        if (m == 3)
        {
            setVector(vertices, left_);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // Set attributes that describe how OpenGL should interpret the vertex data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }
        if (m==4)
        {
            setVector(vertices, right_);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // Set attributes that describe how OpenGL should interpret the vertex data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }*/
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
        if (triangulo) {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        if (linea) {
            glBindVertexArray(VAO);
            glDrawArrays(GL_LINE_LOOP, 0, 3);
        }
        if (punto)
        {
            glBindVertexArray(VAO);
            glDrawArrays(GL_POINTS, 0, 3);
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
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        m = 1;
    if (key == GLFW_KEY_DOWN)
        m = 2;
    if (key == GLFW_KEY_LEFT)
        m = 3;
    if (key == GLFW_KEY_RIGHT)
        m = 4;
}
