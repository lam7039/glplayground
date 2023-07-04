#include "imgui.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

void ImGuiWrapper::attach(void *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    io.IniFilename = "debug/imgui.ini";
    io.LogFilename = "log/imgui_log.txt";
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // ImGuiStyle &style = ImGui::GetStyle();
    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    //     style.WindowRounding = 0.0f;
    //     style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    // }

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window, true);
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

void ImGuiWrapper::render(glm::vec3 &positionBackgroundTexture, glm::vec3 &positionMarioTexture) {

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    // ImGui::Begin("My First Tool");
    // if (ImGui::BeginMenuBar()) {
    //     if (ImGui::BeginMenu("File")){
    //         if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
    //         if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
    //         if (ImGui::MenuItem("Close", "Ctrl+W"))  { /* Do stuff */ }
    //         ImGui::EndMenu();
    //     }
    //     ImGui::EndMenuBar();
    // }
    // ImGui::End();

    // ImGui::Begin("Hello ImGui!");
    // for (auto& [name, object] : objects) {
    //     switch (object->type) {
    //         case AssetType::IMAGE:
    //             ImGui::Text((name + " Position").c_str());
    //             ImGui::SliderFloat((name + " X").c_str(), &object->position.x, 0.0f, 1280.0f - 200.0f);
    //             ImGui::SliderFloat((name + " Y").c_str(), &object->position.y, 0.0f, 720.0f - 150.0f);

    //             ImGui::Text((name + " Size").c_str());
    //             ImGui::SliderFloat((name + " X").c_str(), &object->size.x, 0.0f, 1280.0f - 200.0f);
    //             ImGui::SliderFloat((name + " Y").c_str(), &object->size.y, 0.0f, 720.0f - 150.0f);
    //         break;
    //     }
    // }
    // ImGui::End();

    ImGui::Begin("Hello ImGui!");

    ImGui::Text("Background Texture Position");
    ImGui::SliderFloat("BPX", &positionBackgroundTexture.x, 0.0f, 1280.0f - 200.0f);
    ImGui::SliderFloat("BPY", &positionBackgroundTexture.y, 0.0f, 720.0f - 150.0f);

    ImGui::Separator();

    ImGui::Text("Mario Texture Position");
    ImGui::SliderFloat("MPX", &positionMarioTexture.x, 0.0f, 1280.0f - 150.0f);
    ImGui::SliderFloat("MPY", &positionMarioTexture.y, 0.0f, 720.0f - 200.0f);
    
    ImGui::End();

    ImGui::EndFrame();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// ImGuiIO &io = ImGui::GetIO();
    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    //     GLFWwindow* backup_current_context = glfwGetCurrentContext();
    //     ImGui::UpdatePlatformWindows();
    //     ImGui::RenderPlatformWindowsDefault();
    //     glfwMakeContextCurrent(backup_current_context);
    // }
}
