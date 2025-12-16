#include "game.hpp"

Game::Game(std::string_view workspace, Renderer& renderer) : renderer(renderer) {
    asset_manager = get_asset_manager();
    asset_manager->set_workspace(workspace);
}

void Game::init(glm::vec2 viewport) {
    std::printf("Current workspace: %s\n", asset_manager->get_workspace().data());

    //TODO: create assets with a file using an AssetLoader
    asset_manager->load_shader("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    asset_manager->load_texture("background", "/assets/image.jpg");
    asset_manager->load_texture("mario", "/assets/mario.png");

    camera_system.init(asset_manager);
    render_system.init(asset_manager);

    //TODO: make a scene manager
    scene = std::make_shared<Scene>(viewport);
    scene->init();
}

void Game::quit() {
    scene->destroy();
    asset_manager->destroy_assets();
}

void Game::update() {
    camera_system.update(scene->get_registry());
    render_system.update(scene->get_registry());
}

void Game::render() {
    auto shader = asset_manager->get_shader("main");
    renderer.set_shader(shader);
    renderer.render(scene->get_registry());
}

entt::registry& Game::registry() {
    return scene->get_registry();
}
