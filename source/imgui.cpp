#include "imgui.hpp"
#include "window.hpp"
#include "mesh.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
// #include <glm/gtc/type_ptr.hpp>

// #include <format>

ImGuiWrapper::ImGuiWrapper(glm::vec2 viewport) : viewport(viewport) {}

void ImGuiWrapper::attach(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = "build/imgui.ini";
    io.LogFilename = "log/imgui_log.txt";
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // ImGuiStyle& style = ImGui::GetStyle();
    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    //     style.WindowRounding = 0.0f;
    //     style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    // }

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");
}

void ImGuiWrapper::detach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiWrapper::new_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiWrapper::end_frame() {
    ImGui::EndFrame();
}

void ImGuiWrapper::transform_box(int id, TransformComponent& transform) {
    bool changed = false;

    auto identifier = std::to_string(id);
    ImGui::Text("Entity ID: %s", identifier.c_str());
    changed |= ImGui::SliderFloat(("Position X##" + identifier + "PositionX").c_str(), &transform.position.x, 0.0f, viewport.x);
    changed |= ImGui::SliderFloat(("Position Y##" + identifier + "PositionY").c_str(), &transform.position.y, 0.0f, viewport.y);
    changed |= ImGui::SliderFloat(("Position Z##" + identifier + "PositionZ").c_str(), &transform.position.z, -100.0f, 100.0f);
    changed |= ImGui::SliderFloat(("Size X##" + identifier + "SizeX").c_str(), &transform.scale.x, 0.0f, viewport.x);
    changed |= ImGui::SliderFloat(("Size Y##" + identifier + "SizeY").c_str(), &transform.scale.y, 0.0f, viewport.y);
    ImGui::Separator();
    
    if (changed) {
        // transform.dirty = true;
    }
}

void ImGuiWrapper::set(entt::registry& registry) {
    auto transformables = registry.view<Mesh, TransformComponent>();

    new_frame();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::Begin("Entities");

    for (auto [entity, mesh, transform] : transformables.each()) {
        auto id = entt::to_entity(entity);
        transform_box(id, transform);
    }
    
    ImGui::End();

    end_frame();
}

void ImGuiWrapper::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// ImGuiIO& io = ImGui::GetIO();
    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    //     GLFWwindow* backup_current_context = glfwGetCurrentContext();
    //     ImGui::UpdatePlatformWindows();
    //     ImGui::RenderPlatformWindowsDefault();
    //     glfwMakeContextCurrent(backup_current_context);
    // }
}
