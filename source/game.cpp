#include "game.hpp"

Game::Game(std::string_view workspace, Renderer& renderer) : renderer(renderer) {
    asset_manager = get_asset_manager();
    asset_manager->set_workspace(workspace);
}

void Game::init(glm::vec2 viewport) {
    //TODO: use fmt
    std::printf("Current workspace: %s\n", asset_manager->get_workspace().data());

    //TODO: create assets with a file using an AssetLoader
    asset_manager->load_shader("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    asset_manager->load_texture("background", "/assets/image.jpg");
    asset_manager->load_texture("mario", "/assets/mario.png");

    auto shader = asset_manager->get_shader("main");
    shader->bind();

    scene = std::make_shared<Scene>(viewport);
    scene->init();
}

void Game::quit() {
    scene->destroy();
    asset_manager->destroy_assets();
}

void Game::update() {
    scene->update();
}

void Game::render() {
    auto shader = asset_manager->get_shader("main");
    renderer.set_shader(shader);
    renderer.render_scene(*scene);
}
