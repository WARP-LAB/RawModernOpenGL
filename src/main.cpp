//  main.cpp
//  RawModernOpenGL
//
//  Created by kroko on 02.04.18.

#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void setup() {
    
}

void exit() {
    
}

void draw() {
    glClearColor(
                 sin(glfwGetTime() * 1.0f),
                 cos(glfwGetTime() * 3.0f),
                 sin(glfwGetTime() * 0.5f),
                 1.0f
                 );
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, const char * argv[]) {
    
    std::cout << "Hello modern OpenGL!" << std::endl;

    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "GLFW init failed. ABORTING." << std::endl;
        return -1;
    }
    
    // Set all the required options for GLFW http://www.glfw.org/faq.html#how-do-i-create-an-opengl-30-context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    // Create a windowed mode window
    GLFWwindow *window = glfwCreateWindow(600, 600, "Raw Modern OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window. ABORTING." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Get frame buffer actual size
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight );
    
    // Make the window's context current
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW http://glew.sourceforge.net/basic.html
    glewExperimental = GL_TRUE; // This is not "experimental" it should read "modern".
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "GLEW init failed. ABORTING." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Define the viewport dimensions
    glViewport(0, 0, fbWidth, fbHeight);
    
    // Setup function
    setup();
    
    // Loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll for and process events
        glfwPollEvents();
        
        // Draw function
        draw();
        
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    
    // Clean up on exit VAOs, VBOs n stuff
    exit();
    
    // Terminate and clean up GLFW
    glfwTerminate();

    std::cout << "Bye!" << std::endl;
    
    return 0;
}
