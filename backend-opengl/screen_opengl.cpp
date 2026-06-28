// screen drawing functions, opengl implementation
#include "maxgl.h"
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <math.h>

#include <screen.h>
#include <string.h>

#define WIDTH 160  
#define HEIGHT 144

GLFWwindow* window;
GLuint program;
GLuint vao;
GLuint vbo;
GLuint texture;

#define colorArraySize WIDTH * HEIGHT * 3
GLubyte colors[colorArraySize];  // Array of colors (RGB format)

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout(location = 0) in vec2 position;\n"
    "out vec2 texCoord;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(position * 2.0 - 1.0, 0.0, 1.0);\n"
    "    texCoord = position;\n"
    "}\n";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "uniform sampler2D colorTexture;\n"
    "in vec2 texCoord;\n"
    "out vec4 fragColor;\n"
    "void main()\n"
    "{\n"
    "    fragColor = texture(colorTexture, texCoord);\n"
    "}\n";

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void setupShaders()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void setupBuffers()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat vertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

void setupTexture()
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void updateTexture()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, colors);
}

void render()
{
    updateTexture();
    glUseProgram(program);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(program, "colorTexture"), 0);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void cleanup()
{
    glDeleteProgram(program);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &texture);
    glfwDestroyWindow(window);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int Screen::Initialize() {
    if (!glfwInit())
    {
        return -1;
    }

    //glfwWindowHint(GLFW_CONTEXT_MAJOR_VERSION, 3);
    //glfwWindowHint(GLFW_CONTEXT_MINOR_VERSION, 3);
    //glfwWindowHint(GLFW_CONTEXT_PROFILE_MASK, GLFW_CONTEXT_PROFILE_CORE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "", NULL, NULL);
    if (!window)
    {
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(glewError));
        glfwDestroyWindow(window);
        return -1;
    }

    setupShaders();
    setupBuffers();
    setupTexture();

    return 0;
}

float deltaTime = 1.0;

float GetDeltaTime() {
    return deltaTime;
}

double lastFrameTimestamp = 0.0;

int Screen::Update() {
    glfwPollEvents();
    double currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrameTimestamp;
    lastFrameTimestamp = currentTime;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    //glClear(GL_COLOR_BUFFER_BIT);

    render();
    glfwSwapBuffers(window);

    return glfwWindowShouldClose(window);
}

void Screen::Cleanup() {
    cleanup(); 
}

void Screen::Clear() {
    memset(colors, 0, WIDTH * HEIGHT * 3);
}

void Screen::SetPixel(int x, int y, Color color) {
    unsigned int pixelIndex = (y * GetWidth() + x) * 3;
    if (pixelIndex > colorArraySize)
        return;

    colors[pixelIndex] = color.r;
    colors[pixelIndex + 1] = color.g;
    colors[pixelIndex + 2] = color.b;
}

int Screen::GetHeight() {
    return HEIGHT;
}

int Screen::GetWidth() {
    return WIDTH;
}

void Screen::GetResolution(int *width, int *height) { 
    if (width) *width = WIDTH;
    if (height) *height = HEIGHT;
}

Color currentColor;

void Screen::SetDrawColor(Color color){
    currentColor = color;
}

void Screen::DrawPixel(int x, int y) {
    unsigned int pixelIndex = (y * GetWidth() + x) * 3;
    if (pixelIndex > colorArraySize)
        return;
    colors[pixelIndex] = currentColor.r;
    colors[pixelIndex + 1] = currentColor.g;
    colors[pixelIndex + 2] = currentColor.b;
}