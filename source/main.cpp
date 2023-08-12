#include "window.hpp"
#include "imgui.hpp"
#include "assets.hpp"
#include "entity.hpp"
#include "camera.hpp"

#include <glm/glm.hpp>

#include <filesystem>
#include <iostream>

int main(int argc, char **argv) {
    std::filesystem::current_path(std::filesystem::path(argv[0]).parent_path().parent_path());
    std::printf("Current workspace: %s\n", get_workspace().c_str());

    Window window("glplayground");
    ImGuiWrapper imgui;

    load_asset<Shader>("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    load_asset<Texture>("background", "/assets/image.jpg");
    load_asset<Texture>("mario", "/assets/mario.png");

    EntityManager entityManager;
    entityManager.add(std::make_shared<Camera>(window.size()));
    entityManager.add(std::make_shared<DrawableEntity>(glm::vec3 {50.0f, 250.0f, 0.0f}, glm::vec3 {200.0f, 150.0f, 0.0f}, "background"), true);
    entityManager.add(std::make_shared<DrawableEntity>(glm::vec3 {500.0f, 250.0f, 0.0f}, glm::vec3 {150.0f, 200.0f, 0.0f}, "mario"), true);
    entityManager.init();

    // imgui.attach(window.instance());

    while (window.running()) {
        entityManager.update();
        entityManager.draw();

        // imgui.set(background.getPosition(), mario.getPosition(), camera.getPosition(), background.getSize(), mario.getSize(), camera.getSize());
        // imgui.render();

        window.swap();
        window.pollEvents();
    }

    // imgui.detach();
    clear_assets();
    
    entityManager.destroy();
    window.destroy();
    
    return 0;
}
