#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <math.h>

#define WIDTH 640
#define HEIGHT 480

GLFWwindow* window;
GLuint program;
GLuint vao;
GLuint vbo;
GLuint texture;

int offset;
int offset2;

GLubyte colors[WIDTH * HEIGHT * 3];  // Array of colors (RGB format)

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
}

void drawSineWave(GLubyte colorArray[], int width, int height, int amplitude, float frequency, float of) {
    float increment = 2.0 * 3.14 / width;
    int midPoint = height / 2;
    int x, y;

    for (x = 0; x < width; x++) {
        y = (int)round(amplitude * sin(frequency * x * increment + of));
        y += midPoint;

        if (y >= 0 && y < height) {
            int pixelIndex = (y * width + x) * 3; // Assuming RGBA format

            // Set the color values for the pixel
            colorArray[pixelIndex] = 255;     // Red component
            colorArray[pixelIndex + 1] = 0; // Green component
            colorArray[pixelIndex + 2] = 0; // Blue component
            //colorArray[pixelIndex + 3] = 1.0; // Alpha component
        }
    }
    for (x = 0; x < width; x++) {
        y = (int)round(amplitude * sin(frequency * x * increment + of + 0.5));
        y += midPoint;

        if (y >= 0 && y < height) {
            int pixelIndex = (y * width + x) * 3; // Assuming RGBA format

            // Set the color values for the pixel
            colorArray[pixelIndex] = 0;     // Red component
            colorArray[pixelIndex + 1] = 255; // Green component
            colorArray[pixelIndex + 2] = 0; // Blue component
            //colorArray[pixelIndex + 3] = 1.0; // Alpha component
        }
    }
    for (x = 0; x < width; x++) {
        y = (int)round(amplitude * sin(frequency * x * increment + of + 1.0));
        y += midPoint;

        if (y >= 0 && y < height) {
            int pixelIndex = (y * width + x) * 3; // Assuming RGBA format

            // Set the color values for the pixel
            colorArray[pixelIndex] = 0;     // Red component
            colorArray[pixelIndex + 1] = 0; // Green component
            colorArray[pixelIndex + 2] = 255; // Blue component
            //colorArray[pixelIndex + 3] = 1.0; // Alpha component
        }
    }
}

void clearFramebuffer()
{
    for (int i = 0; i < WIDTH * HEIGHT * 3; i++)
    {
        colors[i] = 0;
    }
}

/*void handleInput(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_UP)
        {
            offset++;
            printf("%d\n", offset);
        }
        else if (event.key.keysym.sym == SDLK_DOWN)
        {
            offset--;
            printf("%d\n", offset);
        }
        else if (event.key.keysym.sym == SDLK_LEFT)
        {
            offset2--;
            printf("%d\n", offset2);
        }
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
            offset2++;
            printf("%d\n", offset2);
        }
    }
}*/

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char *argv[])
{
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

    offset2 = 30;
    offset = 30;

    float t = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        t = t + 0.05;

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
        clearFramebuffer();
        drawSineWave(colors, WIDTH, HEIGHT, 10 + offset2, 0.1f * offset, t);

    }

    return 0;
}
