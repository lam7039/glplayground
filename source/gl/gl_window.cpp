#define GLFW_INCLUDE_NONE
#include "window.hpp"
#include "gl/gl.hpp"
#include <glfw/glfw3.h>

void Window::GLFWwindowDeleter::operator()(GLFWwindow *window) {
    glfwDestroyWindow(window);
}

Window::Window(const std::string &title, glm::vec2 size, glm::vec2 position) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    window.reset(glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr));

    glfwMakeContextCurrent(window.get());
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        destroy();
        return;
    }
    glfwSwapInterval(1);

    std::cout << "Vendor graphic card:  " << glGetString(GL_VENDOR) << std::endl
              << "Renderer:             " << glGetString(GL_RENDERER) << std::endl
              << "GL version:           " << glGetString(GL_VERSION) << std::endl
              << "GLSL version:         " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    CHECK_GL_ERROR(glViewport(position.x, position.y, size.x, size.y));

    // glfwWindowHint(GLFW_DECORATED, false); // No titlebar / resize stuff
    swap();
}

glm::vec2 Window::size() const {
    int width, height;
    glfwGetFramebufferSize(window.get(), &width, &height);
    return glm::vec2 {width, height};
}

bool Window::running() {
    return !glfwWindowShouldClose(window.get());
}

GLFWwindow *Window::instance() const {
    return window.get();
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        std::cout << "Test keypress" << std::endl;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Window::poll_events() {
    glfwSetKeyCallback(window.get(), key_callback);
    glfwPollEvents();
}

void Window::swap() {
    glfwSwapBuffers(window.get());
}

void Window::close() {
    glfwSetWindowShouldClose(window.get(), GLFW_TRUE);
}

void Window::destroy() {
    window.reset();
    glfwTerminate();
}
