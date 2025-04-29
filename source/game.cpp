#include "game.hpp"
#include "camera.hpp"
#include "entities/player.hpp"
#include "entities/background.hpp"

Game::Game(Renderer& renderer) : renderer(renderer) {
    asset_manager = get_asset_manager();
}

void Game::init(glm::vec2 viewport) {
    std::printf("Current workspace: %s\n", asset_manager->get_workspace().c_str());

    //TODO: create assets with a file using an AssetLoader
    //TODO: limit asset loading to only loading scene assets (as in a assets_to_load method from a Scene class) 
    asset_manager->load_shader("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    asset_manager->load_texture("background", "/assets/image.jpg");
    asset_manager->load_texture("mario", "/assets/mario.png");
    asset_manager->init_assets();

    renderer.set_shader(*asset_manager->get_shader("main"));

    //TODO: create entities with a file using a SceneLoader
    entity_manager = std::make_unique<EntityManager>();
    entity_manager->add_entity(std::make_shared<Camera>(viewport));
    entity_manager->add_entity(std::make_shared<Background>(viewport.x, viewport.y));
    entity_manager->add_entity(std::make_shared<Player>());

    entity_manager->init_entities();
}

void Game::quit() {
    entity_manager->destroy_entities();
    asset_manager->destroy_assets();
}

void Game::update() {
    entity_manager->update_entities();
    entity_manager->update_drawables();
}

void Game::render() {
    //TODO: render only a specific scene
    renderer.render(entity_manager->get_drawables());
}
