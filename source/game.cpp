#include "game.hpp"

Game::Game(const std::string& workspace, Renderer& renderer) : renderer(renderer) {
    asset_manager = get_asset_manager();
    asset_manager->set_workspace(workspace);
}

void Game::init(glm::vec2 viewport) {
    std::printf("Current workspace: %s\n", asset_manager->get_workspace().c_str());

    //TODO: create assets with a file using an AssetLoader
    asset_manager->load_shader("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    asset_manager->load_texture("background", "/assets/image.jpg");
    asset_manager->load_texture("mario", "/assets/mario.png");
    asset_manager->init_assets();

    auto shader = asset_manager->get_shader("main").lock();
    shader->load();
    shader->bind();

    // scene.init();
}

void Game::quit() {
    // scene.destroy();
    asset_manager->destroy_assets();
}

void Game::update() {
    // scene.update();
}

void Game::render() {
    // auto& shader = asset_manager->get_shader("main");
    // renderer.set_shader(shader);

    //TODO: render only a specific scene
    // auto drawables = entity_manager->get_drawables();
    // renderer.render(entity_manager->get_drawables());
}
