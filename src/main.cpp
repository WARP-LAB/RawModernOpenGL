//  main.cpp
//  RawModernOpenGL
//
//  Created by kroko on 02.04.18.

#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4

#include <glm/gtc/constants.hpp> // glm::pi
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <glm/gtx/string_cast.hpp> // glm::to_string
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

GLsizei fbWidth, fbHeight;
glm::ivec2 screenSize(800, 600);
glm::vec2 mousePrev(0.0f);
glm::vec2 mouseCurr(0.0f);
glm::vec2 mouseDelta(0.0f);

void setup() {
    glViewport(0, 0, fbWidth, fbHeight);
    
    // Enable multisample
    glEnable(GL_MULTISAMPLE);
    glFrontFace(GL_CCW);
    
    // Cull
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    // Enable depth test & accept closer fragment
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // Set poligon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void exit() {
    
}

void update() {
    
}

void draw() {
    glClearColor(
                 sin(glfwGetTime() * 1.0f),
                 cos(glfwGetTime() * 3.0f),
                 sin(glfwGetTime() * 0.5f),
                 1.0f
                 );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void keyClbk(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        std::cout << "Cursor mode toggled" << std::endl;
        if(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        return;
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        std::cout << "glPolygonMode mode changed to point" << std::endl;
        return;
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        std::cout << "glPolygonMode mode changed to line" << std::endl;
        return;
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        std::cout << "glPolygonMode mode changed to fill" << std::endl;
        return;
    }
}

static void resizeClbk(GLFWwindow* window, int width, int height)
{
    fbWidth = width;
    fbHeight = height;
    glViewport(0, 0, fbWidth, fbHeight);
    std::cout << "Window resized: " << fbWidth << "," << fbHeight << std::endl;
}

static void mousePositionClbk(GLFWwindow* window, double xpos, double ypos)
{
    mouseCurr = glm::vec2(xpos, ypos);
    mouseDelta = mouseCurr - mousePrev;
    mousePrev = mouseCurr;
    std::cout << "Mouse moved: " << glm::to_string(mouseCurr) << std::endl;
}

static void mouseEnteredClbk(GLFWwindow* window, int entered)
{
    if (entered) {
        std::cout << "Mouse entered window" << std::endl;
    } else {
        std::cout << "Mouse left window" << std::endl;
    }
}

static void mouseButtonClbk(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "Mouse left button clicked" << std::endl;
    }
}

static void scrollClbk(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << "Mouse scrolled: " << xoffset << "," << yoffset << std::endl;
}

static void glfwErrorClbk(int error, const char* description)
{
    std::cerr << "GLFW error: " << description << std::endl;
}

int main(int argc, const char * argv[]) {
    
    std::cout << "Hello modern OpenGL!" << std::endl;

    // Initialize GLFW
    glfwSetErrorCallback(glfwErrorClbk);
    if (!glfwInit())
    {
        std::cerr << "GLFW init failed. ABORTING." << std::endl;
        return -1;
    }
    
    // If modern OpenGL then we basically go all the way up to 4.1
    // This http://www.glfw.org/faq.html#how-do-i-create-an-opengl-30-context explains why we set GLFW_OPENGL_FORWARD_COMPAT
    // Thus setting 3.2 will give us maximum OpenGL version possible on your hardware https://support.apple.com/lv-lv/HT202823
    // Meaning that we can use #version 150, 330, 400, 410 in shaderland which is nice, isn't it?
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Extra hints
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    // MSAA
    glfwWindowHint(GLFW_SAMPLES, 0);
    
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    screenSize.x = mode->width;
    screenSize.y = mode->height;
    
    std::cout << "Primary screen size: " << glm::to_string(screenSize) << std::endl;
    
    // Create a windowed mode window
    GLFWwindow *window = glfwCreateWindow(600, 600, "Raw Modern OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window. ABORTING." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Setup event callbacks
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetKeyCallback(window, keyClbk);
    glfwSetFramebufferSizeCallback(window, resizeClbk);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mousePositionClbk);
    glfwSetCursorEnterCallback(window, mouseEnteredClbk);
    glfwSetMouseButtonCallback(window, mouseButtonClbk);
    glfwSetScrollCallback(window, scrollClbk);
    
    // Get frame buffer actual size
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight );
    
    // Make the window's context current
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW http://glew.sourceforge.net/basic.html
    glewExperimental = GL_TRUE; // This is not "experimental" it should read "modern".
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW init failed. ABORTING." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    std::cout << "Vendor: " << (char*)glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL version: " << (char*)glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << (char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
    // Swap interval
    glfwSwapInterval(1);
    
    // Define the viewport dimensions
    glViewport(0, 0, fbWidth, fbHeight);
    
    // Setup function
    setup();
    
    // Loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll for and process events
        glfwPollEvents();
        
        // Update function
        update();
        
        // Draw function
        draw();
        
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    
    // Clean up on exit VAOs, VBOs n stuff
    exit();
    
    // Terminate and clean up GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Bye!" << std::endl;
    
    return 0;
}
