#include "game.hpp"
#include "camera.hpp"
#include "entities/player.hpp"
#include "entities/background.hpp"
#include "asset_manager.hpp"

void Game::init(float width, float height) {
    std::printf("Current workspace: %s\n", get_asset_manager().get_workspace().c_str());

    //TODO: should I load assets in main? perhaps limit loading to assets to load from a scene (as in a assets_to_load method from a Scene class) 
    get_asset_manager().load_shader("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    get_asset_manager().load_texture("background", "/assets/image.jpg");
    get_asset_manager().load_texture("mario", "/assets/mario.png");

    //TODO: create entities with a file
    entity_manager = std::make_unique<EntityManager>();
    entity_manager->add_entity(std::make_shared<Camera>(glm::vec2 {width, height}));
    entity_manager->add_entity(std::make_shared<Background>(width, height));
    entity_manager->add_entity(std::make_shared<Player>());

    entity_manager->init_entities();
}

void Game::quit() {
    entity_manager->destroy_entities();
    get_asset_manager().destroy_assets();
}

void Game::update() {
    entity_manager->update_entities();
}

void Game::render(Renderer& renderer) {
    //TODO: render only a specific scene
    renderer.render(entity_manager->get_drawables());
}
