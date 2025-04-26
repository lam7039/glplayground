#include "window.hpp"
// #include "imgui.hpp"
#include "game.hpp"
#include "renderer.hpp"
#include "gl/gl_renderer.hpp"
#include "asset_manager.hpp"

#include <filesystem>

int main(int argc, char **argv) {
    std::filesystem::current_path(std::filesystem::path(argv[0]).parent_path().parent_path());

    Window window("glplayground");
    // ImGuiWrapper imgui(window.size());

    std::shared_ptr<AssetManager> asset_manager = get_asset_manager();
    std::printf("Current workspace: %s\n", asset_manager->get_workspace().c_str());

    //TODO: figure out place to load assets. 
    //TODO: limit asset loading to only loading scene assets (as in a assets_to_load method from a Scene class) 
    asset_manager->load_shader("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    asset_manager->load_texture("background", "/assets/image.jpg");
    asset_manager->load_texture("mario", "/assets/mario.png");

    Renderer renderer;
    renderer.init(std::make_unique<GLRenderer>());

    Game game;
    game.init(window.size().x, window.size().y);

    // imgui.attach(window.instance());

    while (window.running()) {
        game.update();
        game.render(renderer);

        // imgui.render();

        renderer.clear();

        window.swap();
        window.poll_events();
    }

    // imgui.detach();

    renderer.destroy();
    game.quit();
    asset_manager->destroy_assets();

    window.destroy();
    return 0;
}
