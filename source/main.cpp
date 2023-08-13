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
    ImGuiWrapper imgui(window.size());

    load_asset<Shader>("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    load_asset<Texture>("background", "/assets/image.jpg");
    load_asset<Texture>("mario", "/assets/mario.png");

    add_entity(std::make_shared<Camera>(window.size()));
    add_entity<DrawableEntity>(glm::vec3 {50.0f, 250.0f, 0.0f}, glm::vec3 {200.0f, 150.0f, 0.0f}, "background");
    add_entity<DrawableEntity>(glm::vec3 {500.0f, 250.0f, 0.0f}, glm::vec3 {150.0f, 200.0f, 0.0f}, "mario");
    init_entities();

    imgui.attach(window.instance());

    while (window.running()) {
        update_entities();
        render_drawables();

        imgui.set(get_drawables());
        imgui.render();

        window.swap();
        window.pollEvents();
    }

    imgui.detach();
    clear_assets();

    destroy_entities();
    window.destroy();
    
    return 0;
}
