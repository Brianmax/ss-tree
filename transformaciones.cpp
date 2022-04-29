#include <iostream>
#include <random>
#include <math.h>
#include <time.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vertex.cpp"
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
bool r = false, l = false, u = false, d = false, ro = false;
float up[3] = {0, 0.01, 0};
float down[3] = {0, -0.01, 0};
float left_[3] = {-0.01, 0, 0};
float right_[3] = {0.01, 0, 0};
const int M = 3;
const int N = 3;
const int P = 1;
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
void changeArray(float *vertex, float *newVertex, int len)
{
    for (int i = 0; i < len; i = i + 3) {
        newVertex[i] = -1 * vertex[i];
        newVertex[i + 1] = vertex[i + 1];
        newVertex[i + 2] = 0.0f;
    }
}
void multi(float mat1[M][N], float mat2[M][P], float answer[M][P])
{
    for (int i = 0; i < M; i++)
    {
        for (int e = 0; e < P; e++)
        {
            for (int j = 0; j < M; j++)
                answer[i][e] = answer[i][e] + mat1[i][j]*mat2[j][e];
        }
    }
}
void rotateFunction(float matriz[3][3], float *points, int len)
{
    float Point[3][1] = {{}};

    for (int i = 0; i < len; i = i + 3)
    {
        float NewPoint[3][1] = {{}};
        Point[0][0] = points[i];
        Point[1][0] = points[i + 1];
        Point[2][0] = 1;
        multi(matriz, Point, NewPoint);
        points[i] = NewPoint[0][0];
        points[i + 1] = NewPoint[1][0];
        points[i + 2] = 0;
    }
}
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    //glfwSetKeyCallback(window, key_callback);
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


    float marco[18] = {
            -0.9f, 0.95f, 0.0f,
            0.9f, 0.95f, 0.0f,
            0.9f, -0.9f, 0.0f,
            -0.9f, -0.9f, 0.0f,
            0.9f, -0.9f, 0.0f,
            -0.9f, 0.95f, 0.0f,

    };

    float marcoLinea[12] = {
            -0.9f, 0.95f, 0.0f,
            0.9f, 0.95f, 0.0f,
            0.9f, -0.9f, 0.0f,
            -0.9f, -0.9f, 0.0f,

    };

    float lineasHoja[12] = {
            -0.06f, -0.9f, 0.0f,
            -0.82f, 0.28f, 0.0f,
            0.06f, -0.91f, 0.0f,
            0.82f, 0.28f, 0.0f,
    };

    unsigned int VBOMarcoL, VAOMarcoL;
    glGenVertexArrays(1, &VAOMarcoL);
    glGenBuffers(1, &VBOMarcoL);

    // Bind VAO, then bind VBO
    glBindVertexArray(VAOMarcoL);
    glBindBuffer(GL_ARRAY_BUFFER, VBOMarcoL);

    // Copy the vertex data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(marcoLinea), marcoLinea, GL_STATIC_DRAW);

    // Set attributes that describe how OpenGL should interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int VBOLines, VAOLines;
    glGenVertexArrays(1, &VAOLines);
    glGenBuffers(1, &VBOLines);

    // Bind VAO, then bind VBO
    glBindVertexArray(VAOLines);
    glBindBuffer(GL_ARRAY_BUFFER, VBOLines);

    // Copy the vertex data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineasHoja), lineasHoja, GL_STATIC_DRAW);

    // Set attributes that describe how OpenGL should interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Marco
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO, then bind VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy the vertex data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(marco), marco, GL_STATIC_DRAW);

    // Set attributes that describe how OpenGL should interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    float tallo[18] = {
            0.05f, -0.05f, 0.0f, //top right
            0.05, -0.9f, 0.0f, //bottom right
            -0.05f, -0.9, 0.0f, //bottom left

            -0.05f, -0.9, 0.0f, //bottom left
            -0.05, -0.05f, 0.0f, //top left
            0.05f, -0.05f, 0.0f
    };
    float talloLinea[12] = {
            0.05f, -0.06f, 0.0f, //top right
            0.05, -0.9f, 0.0f, //bottom right
            -0.05f, -0.9, 0.0f, //bottom left
            -0.05, -0.07f, 0.0f, //top left
    };

    unsigned int VBOTalloL, VAOTalloL, EBOL;
    glGenVertexArrays(1, &VAOTalloL);
    glGenBuffers(1, &VBOTalloL);
    glGenBuffers(1, &EBOL);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOTalloL);

    glBindBuffer(GL_ARRAY_BUFFER, VBOTalloL);
    glBufferData(GL_ARRAY_BUFFER, sizeof(talloLinea), talloLinea, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int VBOTallo, VAOTallo, EBO;
    glGenVertexArrays(1, &VAOTallo);
    glGenBuffers(1, &VBOTallo);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOTallo);

    glBindBuffer(GL_ARRAY_BUFFER, VBOTallo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tallo), tallo, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int VBOHoja, VAOHoja;
    glGenVertexArrays(1, &VAOHoja);
    glGenBuffers(1, &VBOHoja);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOHoja);

    glBindBuffer(GL_ARRAY_BUFFER, VBOHoja);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hoja1), hoja1, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    float rightLeafVertex[216];
    changeArray(hoja1, rightLeafVertex, 216);

    unsigned int VBORightLeaf, VAOHojaRightLeaf;
    glGenVertexArrays(1, &VAOHojaRightLeaf);
    glGenBuffers(1, &VBORightLeaf);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOHojaRightLeaf);

    glBindBuffer(GL_ARRAY_BUFFER, VBORightLeaf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rightLeafVertex), rightLeafVertex, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int VBOpetaloRight, VAOpetaloRight;
    glGenVertexArrays(1, &VAOpetaloRight);
    glGenBuffers(1, &VBOpetaloRight);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOpetaloRight);

    glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloRight);
    glBufferData(GL_ARRAY_BUFFER, sizeof(petaloRight), petaloRight, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    float petaloLeft[378];
    changeArray(petaloRight, petaloLeft, 378);
    unsigned int VBOpetaloLeft, VAOpetaloLeft;
    glGenVertexArrays(1, &VAOpetaloLeft);
    glGenBuffers(1, &VBOpetaloLeft);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOpetaloLeft);

    glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloLeft);
    glBufferData(GL_ARRAY_BUFFER, sizeof(petaloLeft), petaloLeft, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int VBOpetaloCentro, VAOpetaloCentro;
    glGenVertexArrays(1, &VAOpetaloCentro);
    glGenBuffers(1, &VBOpetaloCentro);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOpetaloCentro);

    glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro);
    glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro), petaloCentro, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int VBOLineaHoja1, VAOLineaHoja1;
    glGenVertexArrays(1, &VAOLineaHoja1);
    glGenBuffers(1, &VBOLineaHoja1);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOLineaHoja1);

    glBindBuffer(GL_ARRAY_BUFFER, VBOLineaHoja1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Linehoja1), Linehoja1, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    float lineHoja2[144];
    changeArray(Linehoja1, lineHoja2, 144);
    unsigned int VBOLineaHoja2, VAOLineaHoja2;
    glGenVertexArrays(1, &VAOLineaHoja2);
    glGenBuffers(1, &VBOLineaHoja2);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOLineaHoja2);

    glBindBuffer(GL_ARRAY_BUFFER, VBOLineaHoja2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineHoja2), lineHoja2, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    float petaloCentro2[135];
    changeArray(petaloCentro, petaloCentro2, 135);
    unsigned int VBOpetaloCentro2, VAOpetaloCentro2;
    glGenVertexArrays(1, &VAOpetaloCentro2);
    glGenBuffers(1, &VBOpetaloCentro2);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOpetaloCentro2);

    glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro2), petaloCentro2, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int VBOlineaPetaloR, VAOlineaPetaloR;
    glGenVertexArrays(1, &VAOlineaPetaloR);
    glGenBuffers(1, &VBOlineaPetaloR);
    glBindVertexArray(VAOlineaPetaloR);

    glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloR);
    glBufferData(GL_ARRAY_BUFFER, sizeof(LinepetaloRight), LinepetaloRight, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    float lineaPetaloL[252];
    changeArray(LinepetaloRight, lineaPetaloL, 252);
    unsigned int VBOlineaPetaloL, VAOlineaPetaloL;
    glGenVertexArrays(1, &VAOlineaPetaloL);
    glGenBuffers(1, &VBOlineaPetaloL);
    glBindVertexArray(VAOlineaPetaloL);

    glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloL);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineaPetaloL), lineaPetaloL, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int VBOlineaPetaloC1, VAOlineaPetaloC1;
    glGenVertexArrays(1, &VAOlineaPetaloC1);
    glGenBuffers(1, &VBOlineaPetaloC1);
    glBindVertexArray(VAOlineaPetaloC1);

    glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloC1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(LineapetaloCentroL), LineapetaloCentroL, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    float LineapetaloCentroR[135];
    changeArray(LineapetaloCentroL, LineapetaloCentroR, 135);
    unsigned int VBOlineaPetaloC2, VAOlineaPetaloC2;
    glGenVertexArrays(1, &VAOlineaPetaloC2);
    glGenBuffers(1, &VBOlineaPetaloC2);
    glBindVertexArray(VAOlineaPetaloC2);

    glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloC2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(LineapetaloCentroR), LineapetaloCentroR, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glPointSize(8);
    glLineWidth(10);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        int vertexColorLocation;
        glUseProgram(shaderProgram);
        vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.15f, 0.32f, 0.76f, 1.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.17f, 0.61f, 0.05f, 1.0f);
        glBindVertexArray(VAOHojaRightLeaf);
        glDrawArrays(GL_TRIANGLES, 0, 1000);
        glBindVertexArray(VAOHoja);
        glDrawArrays(GL_TRIANGLES, 0, 1000);



        vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.05f, 0.92f, 0.93f, 1.0f);
        glBindVertexArray(VAOpetaloRight);
        glDrawArrays(GL_TRIANGLES, 0, 1000);

        glBindVertexArray(VAOpetaloLeft);
        glDrawArrays(GL_TRIANGLES, 0, 1000);

        glBindVertexArray(VAOpetaloCentro);
        glDrawArrays(GL_TRIANGLES, 0, 1000);

        glBindVertexArray(VAOpetaloCentro2);
        glDrawArrays(GL_TRIANGLES, 0, 1000);

        vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
        glBindVertexArray(VAOlineaPetaloR);
        glDrawArrays(GL_LINES, 0, 100);

        glBindVertexArray(VAOlineaPetaloL);
        glDrawArrays(GL_LINES, 0, 100);

        glBindVertexArray(VAOlineaPetaloC1);
        glDrawArrays(GL_LINES, 0, 100);

        glBindVertexArray(VAOlineaPetaloC2);
        glDrawArrays(GL_LINES, 0, 100);

        glBindVertexArray(VAOLineaHoja1);
        glDrawArrays(GL_LINES, 0, 1000);

        glBindVertexArray(VAOLineaHoja2);
        glDrawArrays(GL_LINES, 0, 1000);

        glBindVertexArray(VAOLines);
        glDrawArrays(GL_LINES, 0, 100);

        glBindVertexArray(VAOTalloL);
        glDrawArrays(GL_LINES, 0, 100);

        glBindVertexArray(VAOMarcoL);
        glDrawArrays(GL_LINE_LOOP, 0, 4);

        vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.73f, 0.29f, 0.0f, 1.0f);
        glBindVertexArray(VAOTallo);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        if (r)
        {
            rotateFunction(translateMas, lineasHoja, 12);
            glad_glBindVertexArray(VAOLines);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLines);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineasHoja), lineasHoja, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Marco Triangulo
            rotateFunction(translateMas, marco, 18);
            glad_glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(marco), marco, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Hoja izquierda Triangulos
            rotateFunction(translateMas, hoja1, 216);
            glad_glBindVertexArray(VAOHoja);
            glBindBuffer(GL_ARRAY_BUFFER, VBOHoja);
            glBufferData(GL_ARRAY_BUFFER, sizeof(hoja1), hoja1, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Hoja derecha Triangulos
            rotateFunction(translateMas, rightLeafVertex, 216);
            glad_glBindVertexArray(VAOHojaRightLeaf);
            glBindBuffer(GL_ARRAY_BUFFER, VBORightLeaf);
            glBufferData(GL_ARRAY_BUFFER, sizeof(rightLeafVertex), rightLeafVertex, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Tallo Triangulos
            rotateFunction(translateMas, tallo, 18);
            glad_glBindVertexArray(VAOTallo);
            glBindVertexArray(VAOTallo);

            glBindBuffer(GL_ARRAY_BUFFER, VBOTallo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(tallo), tallo, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            //Petalo right triangulos

            rotateFunction(translateMas, petaloRight, 378);
            glad_glBindVertexArray(VAOpetaloRight);
            glBindVertexArray(VAOpetaloRight);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloRight);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloRight), petaloRight, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo left triangulos
            rotateFunction(translateMas, petaloLeft, 378);
            glad_glBindVertexArray(VAOpetaloLeft);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloLeft);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloLeft), petaloLeft, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo centro triangulos
            rotateFunction(translateMas, petaloCentro, 135);
            glad_glBindVertexArray(VAOpetaloCentro);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro), petaloCentro, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo centro triangulos
            rotateFunction(translateMas, petaloCentro2, 135);
            glad_glBindVertexArray(VAOpetaloCentro2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro2), petaloCentro2, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea hoja 1
            rotateFunction(translateMas, Linehoja1, 144);
            glad_glBindVertexArray(VAOLineaHoja1);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLineaHoja1);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Linehoja1), Linehoja1, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea hoja 2
            rotateFunction(translateMas, lineHoja2, 144);
            glad_glBindVertexArray(VAOLineaHoja2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLineaHoja2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineHoja2), lineHoja2, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo Centro 2
            /*rotateFunction(rotacion, petaloCentro2, 135);
            glad_glBindVertexArray(VAOpetaloCentro2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro2), petaloCentro2, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);*/
            //Linea Petalo r
            rotateFunction(translateMas, LinepetaloRight, 252);
            glad_glBindVertexArray(VAOlineaPetaloR);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloR);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LinepetaloRight), LinepetaloRight, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            //Linea Petalo r
            rotateFunction(translateMas, lineaPetaloL, 252);
            glad_glBindVertexArray(VAOlineaPetaloL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineaPetaloL), lineaPetaloL, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea Petalo L
            rotateFunction(translateMas, LineapetaloCentroL, 135);
            glad_glBindVertexArray(VAOlineaPetaloC1);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloC1);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LineapetaloCentroL), LineapetaloCentroL, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea Petalo L
            rotateFunction(translateMas, LineapetaloCentroR, 135);
            glad_glBindVertexArray(VAOlineaPetaloC2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloC2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LineapetaloCentroR), LineapetaloCentroR, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Marco Linea
            rotateFunction(translateMas, marcoLinea, 12);
            glad_glBindVertexArray(VAOMarcoL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOMarcoL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(marcoLinea), marcoLinea, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Tallo linea
            rotateFunction(translateMas, talloLinea, 12);
            glad_glBindVertexArray(VAOTalloL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOTalloL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(talloLinea), talloLinea, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            r = false;
        }
        if (l)
        {
            rotateFunction(translateMenos, lineasHoja, 12);
            glad_glBindVertexArray(VAOLines);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLines);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineasHoja), lineasHoja, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Marco Triangulo
            rotateFunction(translateMenos, marco, 18);
            glad_glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(marco), marco, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Tallo Triangulos
            rotateFunction(translateMenos, tallo, 18);
            glad_glBindVertexArray(VAOTallo);
            glBindVertexArray(VAOTallo);

            glBindBuffer(GL_ARRAY_BUFFER, VBOTallo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(tallo), tallo, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Hoja izquierda Triangulos
            rotateFunction(translateMenos, hoja1, 216);
            glad_glBindVertexArray(VAOHoja);
            glBindBuffer(GL_ARRAY_BUFFER, VBOHoja);
            glBufferData(GL_ARRAY_BUFFER, sizeof(hoja1), hoja1, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Hoja derecha Triangulos
            rotateFunction(translateMenos, rightLeafVertex, 216);
            glad_glBindVertexArray(VAOHojaRightLeaf);
            glBindBuffer(GL_ARRAY_BUFFER, VBORightLeaf);
            glBufferData(GL_ARRAY_BUFFER, sizeof(rightLeafVertex), rightLeafVertex, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo right triangulos

            rotateFunction(translateMenos, petaloRight, 378);
            glad_glBindVertexArray(VAOpetaloRight);
            glBindVertexArray(VAOpetaloRight);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloRight);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloRight), petaloRight, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo left triangulos
            rotateFunction(translateMenos, petaloLeft, 378);
            glad_glBindVertexArray(VAOpetaloLeft);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloLeft);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloLeft), petaloLeft, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo centro triangulos
            rotateFunction(translateMenos, petaloCentro, 135);
            glad_glBindVertexArray(VAOpetaloCentro);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro), petaloCentro, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo centro triangulos
            rotateFunction(translateMenos, petaloCentro2, 135);
            glad_glBindVertexArray(VAOpetaloCentro2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro2), petaloCentro2, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea hoja 1
            rotateFunction(translateMenos, Linehoja1, 144);
            glad_glBindVertexArray(VAOLineaHoja1);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLineaHoja1);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Linehoja1), Linehoja1, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea hoja 2
            rotateFunction(translateMenos, lineHoja2, 144);
            glad_glBindVertexArray(VAOLineaHoja2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLineaHoja2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineHoja2), lineHoja2, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo Centro 2
            /*rotateFunction(rotacion, petaloCentro2, 135);
            glad_glBindVertexArray(VAOpetaloCentro2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro2), petaloCentro2, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);*/
            //Linea Petalo r
            rotateFunction(translateMenos, LinepetaloRight, 252);
            glad_glBindVertexArray(VAOlineaPetaloR);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloR);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LinepetaloRight), LinepetaloRight, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            //Linea Petalo r
            rotateFunction(translateMenos, lineaPetaloL, 252);
            glad_glBindVertexArray(VAOlineaPetaloL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineaPetaloL), lineaPetaloL, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea Petalo L
            rotateFunction(translateMenos, LineapetaloCentroL, 135);
            glad_glBindVertexArray(VAOlineaPetaloC1);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloC1);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LineapetaloCentroL), LineapetaloCentroL, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea Petalo L
            rotateFunction(translateMenos, LineapetaloCentroR, 135);
            glad_glBindVertexArray(VAOlineaPetaloC2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloC2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LineapetaloCentroR), LineapetaloCentroR, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Marco Linea
            rotateFunction(translateMenos, marcoLinea, 12);
            glad_glBindVertexArray(VAOMarcoL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOMarcoL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(marcoLinea), marcoLinea, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Tallo linea
            rotateFunction(translateMenos, talloLinea, 12);
            glad_glBindVertexArray(VAOTalloL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOTalloL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(talloLinea), talloLinea, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            l = false;
        }
        if (u)
        {
            rotateFunction(scaleMas, lineasHoja, 12);
            glad_glBindVertexArray(VAOLines);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLines);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineasHoja), lineasHoja, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Marco Triangulo
            rotateFunction(scaleMas, marco, 18);
            glad_glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(marco), marco, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Tallo Triangulos
            rotateFunction(scaleMas, tallo, 18);
            glad_glBindVertexArray(VAOTallo);
            glBindVertexArray(VAOTallo);

            glBindBuffer(GL_ARRAY_BUFFER, VBOTallo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(tallo), tallo, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Hoja izquierda Triangulos
            rotateFunction(scaleMas, hoja1, 216);
            glad_glBindVertexArray(VAOHoja);
            glBindBuffer(GL_ARRAY_BUFFER, VBOHoja);
            glBufferData(GL_ARRAY_BUFFER, sizeof(hoja1), hoja1, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Hoja derecha Triangulos
            rotateFunction(scaleMas, rightLeafVertex, 216);
            glad_glBindVertexArray(VAOHojaRightLeaf);
            glBindBuffer(GL_ARRAY_BUFFER, VBORightLeaf);
            glBufferData(GL_ARRAY_BUFFER, sizeof(rightLeafVertex), rightLeafVertex, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo right triangulos

            rotateFunction(scaleMas, petaloRight, 378);
            glad_glBindVertexArray(VAOpetaloRight);
            glBindVertexArray(VAOpetaloRight);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloRight);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloRight), petaloRight, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo left triangulos
            rotateFunction(scaleMas, petaloLeft, 378);
            glad_glBindVertexArray(VAOpetaloLeft);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloLeft);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloLeft), petaloLeft, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo centro triangulos
            rotateFunction(scaleMas, petaloCentro, 135);
            glad_glBindVertexArray(VAOpetaloCentro);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro), petaloCentro, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo centro triangulos
            rotateFunction(scaleMas, petaloCentro2, 135);
            glad_glBindVertexArray(VAOpetaloCentro2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro2), petaloCentro2, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea hoja 1
            rotateFunction(scaleMas, Linehoja1, 144);
            glad_glBindVertexArray(VAOLineaHoja1);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLineaHoja1);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Linehoja1), Linehoja1, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea hoja 2
            rotateFunction(scaleMas, lineHoja2, 144);
            glad_glBindVertexArray(VAOLineaHoja2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLineaHoja2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineHoja2), lineHoja2, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            //Linea Petalo r
            rotateFunction(scaleMas, LinepetaloRight, 252);
            glad_glBindVertexArray(VAOlineaPetaloR);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloR);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LinepetaloRight), LinepetaloRight, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            //Linea Petalo r
            rotateFunction(scaleMas, lineaPetaloL, 252);
            glad_glBindVertexArray(VAOlineaPetaloL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineaPetaloL), lineaPetaloL, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea Petalo L
            rotateFunction(scaleMas, LineapetaloCentroL, 135);
            glad_glBindVertexArray(VAOlineaPetaloC1);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloC1);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LineapetaloCentroL), LineapetaloCentroL, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea Petalo L
            rotateFunction(scaleMas, LineapetaloCentroR, 135);
            glad_glBindVertexArray(VAOlineaPetaloC2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloC2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LineapetaloCentroR), LineapetaloCentroR, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Marco Linea
            rotateFunction(scaleMas, marcoLinea, 12);
            glad_glBindVertexArray(VAOMarcoL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOMarcoL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(marcoLinea), marcoLinea, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Tallo linea
            rotateFunction(scaleMas, talloLinea, 12);
            glad_glBindVertexArray(VAOTalloL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOTalloL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(talloLinea), talloLinea, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            u = false;
        }
        if (d)
        {
            rotateFunction(scaleMenos, lineasHoja, 12);
            glad_glBindVertexArray(VAOLines);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLines);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineasHoja), lineasHoja, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Marco Triangulo
            rotateFunction(scaleMenos, marco, 18);
            glad_glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(marco), marco, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Tallo Triangulos
            rotateFunction(scaleMenos, tallo, 18);
            glad_glBindVertexArray(VAOTallo);
            glBindVertexArray(VAOTallo);

            glBindBuffer(GL_ARRAY_BUFFER, VBOTallo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(tallo), tallo, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Hoja izquierda Triangulos
            rotateFunction(scaleMenos, hoja1, 216);
            glad_glBindVertexArray(VAOHoja);
            glBindBuffer(GL_ARRAY_BUFFER, VBOHoja);
            glBufferData(GL_ARRAY_BUFFER, sizeof(hoja1), hoja1, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Hoja derecha Triangulos
            rotateFunction(scaleMenos, rightLeafVertex, 216);
            glad_glBindVertexArray(VAOHojaRightLeaf);
            glBindBuffer(GL_ARRAY_BUFFER, VBORightLeaf);
            glBufferData(GL_ARRAY_BUFFER, sizeof(rightLeafVertex), rightLeafVertex, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo right triangulos

            rotateFunction(scaleMenos, petaloRight, 378);
            glad_glBindVertexArray(VAOpetaloRight);
            glBindVertexArray(VAOpetaloRight);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloRight);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloRight), petaloRight, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo left triangulos
            rotateFunction(scaleMenos, petaloLeft, 378);
            glad_glBindVertexArray(VAOpetaloLeft);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloLeft);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloLeft), petaloLeft, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo centro triangulos
            rotateFunction(scaleMenos, petaloCentro, 135);
            glad_glBindVertexArray(VAOpetaloCentro);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro), petaloCentro, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo centro triangulos
            rotateFunction(scaleMenos, petaloCentro2, 135);
            glad_glBindVertexArray(VAOpetaloCentro2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro2), petaloCentro2, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea hoja 1
            rotateFunction(scaleMenos, Linehoja1, 144);
            glad_glBindVertexArray(VAOLineaHoja1);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLineaHoja1);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Linehoja1), Linehoja1, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea hoja 2
            rotateFunction(scaleMenos, lineHoja2, 144);
            glad_glBindVertexArray(VAOLineaHoja2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLineaHoja2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineHoja2), lineHoja2, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            //Linea Petalo r
            rotateFunction(scaleMenos, LinepetaloRight, 252);
            glad_glBindVertexArray(VAOlineaPetaloR);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloR);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LinepetaloRight), LinepetaloRight, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            //Linea Petalo r
            rotateFunction(scaleMenos, lineaPetaloL, 252);
            glad_glBindVertexArray(VAOlineaPetaloL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineaPetaloL), lineaPetaloL, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea Petalo L
            rotateFunction(scaleMenos, LineapetaloCentroL, 135);
            glad_glBindVertexArray(VAOlineaPetaloC1);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloC1);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LineapetaloCentroL), LineapetaloCentroL, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea Petalo L
            rotateFunction(scaleMenos, LineapetaloCentroR, 135);
            glad_glBindVertexArray(VAOlineaPetaloC2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloC2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LineapetaloCentroR), LineapetaloCentroR, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Marco Linea
            rotateFunction(scaleMenos, marcoLinea, 12);
            glad_glBindVertexArray(VAOMarcoL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOMarcoL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(marcoLinea), marcoLinea, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Tallo linea
            rotateFunction(scaleMenos, talloLinea, 12);
            glad_glBindVertexArray(VAOTalloL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOTalloL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(talloLinea), talloLinea, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            d = false;
        }
        if (ro)
        {
            rotateFunction(rotacion, lineasHoja, 12);
            glad_glBindVertexArray(VAOLines);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLines);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineasHoja), lineasHoja, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Marco Triangulo
            rotateFunction(rotacion, marco, 18);
            glad_glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(marco), marco, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Tallo Triangulos
            rotateFunction(rotacion, tallo, 18);
            glad_glBindVertexArray(VAOTallo);
            glBindVertexArray(VAOTallo);

            glBindBuffer(GL_ARRAY_BUFFER, VBOTallo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(tallo), tallo, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Hoja izquierda Triangulos
            rotateFunction(rotacion, hoja1, 216);
            glad_glBindVertexArray(VAOHoja);
            glBindBuffer(GL_ARRAY_BUFFER, VBOHoja);
            glBufferData(GL_ARRAY_BUFFER, sizeof(hoja1), hoja1, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Hoja derecha Triangulos
            rotateFunction(rotacion, rightLeafVertex, 216);
            glad_glBindVertexArray(VAOHojaRightLeaf);
            glBindBuffer(GL_ARRAY_BUFFER, VBORightLeaf);
            glBufferData(GL_ARRAY_BUFFER, sizeof(rightLeafVertex), rightLeafVertex, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo right triangulos

            rotateFunction(rotacion, petaloRight, 378);
            glad_glBindVertexArray(VAOpetaloRight);
            glBindVertexArray(VAOpetaloRight);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloRight);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloRight), petaloRight, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo left triangulos
            rotateFunction(rotacion, petaloLeft, 378);
            glad_glBindVertexArray(VAOpetaloLeft);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloLeft);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloLeft), petaloLeft, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo centro triangulos
            rotateFunction(rotacion, petaloCentro, 135);
            glad_glBindVertexArray(VAOpetaloCentro);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro), petaloCentro, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Petalo centro triangulos
            rotateFunction(rotacion, petaloCentro2, 135);
            glad_glBindVertexArray(VAOpetaloCentro2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOpetaloCentro2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(petaloCentro2), petaloCentro2, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea hoja 1
            rotateFunction(rotacion, Linehoja1, 144);
            glad_glBindVertexArray(VAOLineaHoja1);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLineaHoja1);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Linehoja1), Linehoja1, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea hoja 2
            rotateFunction(rotacion, lineHoja2, 144);
            glad_glBindVertexArray(VAOLineaHoja2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOLineaHoja2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineHoja2), lineHoja2, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            //Linea Petalo r
            rotateFunction(rotacion, LinepetaloRight, 252);
            glad_glBindVertexArray(VAOlineaPetaloR);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloR);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LinepetaloRight), LinepetaloRight, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            //Linea Petalo r
            rotateFunction(rotacion, lineaPetaloL, 252);
            glad_glBindVertexArray(VAOlineaPetaloL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(lineaPetaloL), lineaPetaloL, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea Petalo L
            rotateFunction(rotacion, LineapetaloCentroL, 135);
            glad_glBindVertexArray(VAOlineaPetaloC1);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloC1);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LineapetaloCentroL), LineapetaloCentroL, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Linea Petalo L
            rotateFunction(rotacion, LineapetaloCentroR, 135);
            glad_glBindVertexArray(VAOlineaPetaloC2);
            glBindBuffer(GL_ARRAY_BUFFER, VBOlineaPetaloC2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(LineapetaloCentroR), LineapetaloCentroR, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Marco Linea
            rotateFunction(rotacion, marcoLinea, 12);
            glad_glBindVertexArray(VAOMarcoL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOMarcoL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(marcoLinea), marcoLinea, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Tallo linea
            rotateFunction(rotacion, talloLinea, 12);
            glad_glBindVertexArray(VAOTalloL);
            glBindBuffer(GL_ARRAY_BUFFER, VBOTalloL);
            glBufferData(GL_ARRAY_BUFFER, sizeof(talloLinea), talloLinea, GL_STATIC_DRAW);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        if (r)
        {
            r = false;
        }
        else
            r = true;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        if (l)
        {
            l = false;
        }
        else
            l = true;
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        if (u)
        {
            u = false;
        }
        else
            u = true;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        if (d)
        {
            d = false;
        }
        else
            d = true;
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        if (ro)
        {
            ro = false;
        }
        else
            ro = true;
    }
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
