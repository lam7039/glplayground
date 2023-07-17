
#include "window.hpp"
#include "gl.hpp"

Window::Window(const std::string &title, glm::vec2 size, glm::vec2 position) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    window.reset(glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr));

    glfwMakeContextCurrent((GLFWwindow*)window.get());
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glfwSwapInterval(1);

    std::cout << "Vendor graphic card:  " << glGetString(GL_VENDOR) << std::endl
              << "Renderer:             " << glGetString(GL_RENDERER) << std::endl
              << "GL version:           " << glGetString(GL_VERSION) << std::endl
              << "GLSL version:         " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    CHECK_GL_ERROR(glViewport(position.x, position.y, size.x, size.y));
}

glm::vec2 Window::size() const {
    int width, height;
    glfwGetFramebufferSize((GLFWwindow*)window.get(), &width, &height);
    return glm::vec2 {width, height};
}

bool Window::running() {
    return !glfwWindowShouldClose((GLFWwindow*)window.get());
}

void *Window::instance() const {
    return window.get();
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        std::cout << "Test keypress" << std::endl;
    }
}

void Window::pollEvents() {
    glfwSetKeyCallback((GLFWwindow*)window.get(), keyCallback);
    glfwPollEvents();
}

void Window::swap() {
    glfwSwapBuffers((GLFWwindow*)window.get());
}

void Window::destroy() {
    window.release();
    glfwTerminate();
}