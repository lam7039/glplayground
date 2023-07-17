#include "imgui.hpp"
#include "window.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
// #include <glm/gtc/type_ptr.hpp>

void ImGuiWrapper::attach(GLFWwindow *window) {
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
    ImGui_ImplGlfw_InitForOpenGL(window, true);
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

    ImGui::Text("Background Texture");
    // ImGui::SliderFloat2("Position##backgroundPosition", glm::value_ptr(positionTextureBackground), 0.0f, 1280.0f);
    // ImGui::SliderFloat2("Position##backgroundSize", glm::value_ptr(sizeTextureBackground), 0.0f, 1280.0f);
    ImGui::SliderFloat("Position X##backgroundPositionX", &positionTextureBackground.x, 0.0f, 1280.0f - 200.0f);
    ImGui::SliderFloat("Position Y##backgroundPositionY", &positionTextureBackground.y, 0.0f, 720.0f - 150.0f);
    ImGui::SliderFloat("Size X##backgroundSizeX", &sizeTextureBackground.x, 0.0f, 1280.0f);
    ImGui::SliderFloat("Size Y##backgroundSizeY", &sizeTextureBackground.y, 0.0f, 720.0f);

    ImGui::Separator();

    ImGui::Text("Mario Texture");
    // ImGui::SliderFloat2("Position##marioPosition", glm::value_ptr(positionTextureMario), 0.0f, 1280.0f);
    // ImGui::SliderFloat2("Position##marioSize", glm::value_ptr(sizeTextureMario), 0.0f, 1280.0f);
    ImGui::SliderFloat("Position X##marioPositionX", &positionTextureMario.x, 0.0f, 1280.0f - 150.0f);
    ImGui::SliderFloat("Position Y##marioPositionY", &positionTextureMario.y, 0.0f, 720.0f - 200.0f);
    ImGui::SliderFloat("Size X##marioSizeX", &sizeTextureMario.x, 0.0f, 1280.0f);
    ImGui::SliderFloat("Size Y##marioSizeY", &sizeTextureMario.y, 0.0f, 720.0f);
    
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
