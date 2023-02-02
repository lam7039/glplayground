#include "window.hpp"
#include "gl.hpp"
#include <iostream>

static GLWindow container;

Window::Window(const std::string &title, glm::vec2 size, glm::vec2 position) {
    if (!glfwInit()) {
        return;
    }

    container.window = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);

    glfwMakeContextCurrent(container.window);
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glfwSwapInterval(1);

    std::cout << "Vendor graphic card:  " << glGetString(GL_VENDOR) << std::endl
              << "Renderer:             " << glGetString(GL_RENDERER) << std::endl
              << "GL version:           " << glGetString(GL_VERSION) << std::endl
              << "GLSL version:         " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_SCISSOR_TEST);

    glViewport(position.x, position.y, size.x, size.y);
    this->clearColor();
}

glm::vec2 Window::size() const {
    int width, height;
    glfwGetFramebufferSize(container.window, &width, &height);
    return glm::vec2 {width, height};
}

bool Window::running() {
    return !glfwWindowShouldClose(container.window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::clearColor(glm::vec4 color) {
    glClearColor(color.x, color.y, color.z, color.a);
}

void Window::swap() {
    glfwSwapBuffers(container.window);
}

void Window::destroy() {
    glfwDestroyWindow(container.window);
}

void Window::quit() {
    glfwTerminate();
}
