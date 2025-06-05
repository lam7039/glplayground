// #include "imgui.hpp"
// #include "window.hpp"

// #include <imgui/imgui.h>
// #include <imgui/imgui_impl_glfw.h>
// #include <imgui/imgui_impl_opengl3.h>
// // #include <glm/gtc/type_ptr.hpp>

// // #include <format>

// ImGuiWrapper::ImGuiWrapper(glm::vec2 viewport) : viewport(viewport) {}

// void ImGuiWrapper::attach(GLFWwindow* window) {
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO(); (void)io;
//     io.IniFilename = "build/imgui.ini";
//     io.LogFilename = "log/imgui_log.txt";
//     // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
//     io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
//     // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

//     // ImGuiStyle& style = ImGui::GetStyle();
//     // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
//     //     style.WindowRounding = 0.0f;
//     //     style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//     // }

//     ImGui::StyleColorsDark();
//     ImGui_ImplGlfw_InitForOpenGL(window, true);
//     ImGui_ImplOpenGL3_Init("#version 450");
// }

// void ImGuiWrapper::detach() {
//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImGui::DestroyContext();
// }

// void ImGuiWrapper::new_frame() {
//     ImGui_ImplOpenGL3_NewFrame();
//     ImGui_ImplGlfw_NewFrame();
//     ImGui::NewFrame();
// }

// void ImGuiWrapper::end_frame() {
//     ImGui::EndFrame();
// }

// void ImGuiWrapper::transform_box(std::shared_ptr<Entity>& entity) {
//     // auto identifier = std::to_string(entity->get_id());
//     // ImGui::Text("Entity ID: %s", identifier.c_str());
//     // ImGui::SliderFloat(("Position X##" + identifier + "PositionX").c_str(), &entity->get_position().x, 0.0f, viewport.x - entity->get_size().x);
//     // ImGui::SliderFloat(("Position Y##" + identifier + "PositionY").c_str(), &entity->get_position().y, 0.0f, viewport.y - entity->get_size().y);
//     // ImGui::SliderFloat(("Position Z##" + identifier + "PositionZ").c_str(), &entity->get_position().z, -100.0f, 100.0f);
//     // ImGui::SliderFloat(("Size X##" + identifier + "SizeX").c_str(), &entity->get_size().x, 0.0f, viewport.x);
//     // ImGui::SliderFloat(("Size Y##" + identifier + "SizeY").c_str(), &entity->get_size().y, 0.0f, viewport.y);
//     // ImGui::Separator();
// }

// void ImGuiWrapper::set(std::vector<std::shared_ptr<Entity>> entities) {
//     new_frame();

//     ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

//     ImGui::Begin("Entities");

//     for (auto& entity : entities) {
//         transform_box(entity);
//     }
    
//     ImGui::End();

//     end_frame();
// }

// void ImGuiWrapper::render() {
//     ImGui::Render();
//     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

// 	// ImGuiIO& io = ImGui::GetIO();
//     // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
//     //     GLFWwindow* backup_current_context = glfwGetCurrentContext();
//     //     ImGui::UpdatePlatformWindows();
//     //     ImGui::RenderPlatformWindowsDefault();
//     //     glfwMakeContextCurrent(backup_current_context);
//     // }
// }
