#define GLFW_INCLUDE_NONE
#include "window.hpp"
#include "glfw/glfw3.h"
#include "gl.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

Window::Window(const std::string &title, glm::vec2 size, glm::vec2 position) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent((GLFWwindow*)window);
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    std::cout << "Vendor graphic card:  " << glGetString(GL_VENDOR) << std::endl
              << "Renderer:             " << glGetString(GL_RENDERER) << std::endl
              << "GL version:           " << glGetString(GL_VERSION) << std::endl
              << "GLSL version:         " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // CHECK_GL_ERROR(glEnable(GL_DEPTH_TEST));
    // CHECK_GL_ERROR(glDepthFunc(GL_LEQUAL));
    CHECK_GL_ERROR(glEnable(GL_BLEND));
    CHECK_GL_ERROR(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    // CHECK_GL_ERROR(glEnable(GL_SCISSOR_TEST));

    CHECK_GL_ERROR(glViewport(position.x, position.y, size.x, size.y));
    this->clearColor();
    this->clear();
    this->swap();
}

Window::~Window() {
    glfwTerminate();
}

glm::vec2 Window::size() const {
    int width, height;
    glfwGetFramebufferSize((GLFWwindow*)window, &width, &height);
    return glm::vec2 {width, height};
}

bool Window::running() {
    return !glfwWindowShouldClose((GLFWwindow*)window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::clearColor(glm::vec4 color) {
    CHECK_GL_ERROR(glClearColor(color.x, color.y, color.z, color.a));
}

void Window::clear() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Hello ImGui!");

    ImGui::Text("Some useful text");
    
    ImGui::End();

    CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT));
}

void Window::swap() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers((GLFWwindow*)window);
}

void Window::destroy() {
    glfwDestroyWindow((GLFWwindow*)window);
}
