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


void ImGuiWrapper::newFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiWrapper::endFrame() {
    ImGui::EndFrame();
}

void ImGuiWrapper::set(glm::vec3 &positionTextureBackground, glm::vec3 &positionTextureMario, glm::vec3 &sizeTextureBackground, glm::vec3 &sizeTextureMario) {
    newFrame();

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
    ImGui::SliderFloat("BPX", &positionTextureBackground.x, 0.0f, 1280.0f - 200.0f);
    ImGui::SliderFloat("BPY", &positionTextureBackground.y, 0.0f, 720.0f - 150.0f);

    ImGui::Separator();

    ImGui::Text("Background Texture Size");
    ImGui::SliderFloat("BSX", &sizeTextureBackground.x, 0.0f, 1280.0f);
    ImGui::SliderFloat("BSY", &sizeTextureBackground.y, 0.0f, 720.0f);

    ImGui::Separator();

    ImGui::Text("Mario Texture Position");
    ImGui::SliderFloat("MPX", &positionTextureMario.x, 0.0f, 1280.0f - 150.0f);
    ImGui::SliderFloat("MPY", &positionTextureMario.y, 0.0f, 720.0f - 200.0f);

    ImGui::Separator();

    ImGui::Text("Mario Texture Size");
    ImGui::SliderFloat("MSX", &sizeTextureMario.x, 0.0f, 1280.0f);
    ImGui::SliderFloat("MSY", &sizeTextureMario.y, 0.0f, 720.0f);
    
    ImGui::End();

    endFrame();
}

void ImGuiWrapper::render() {
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