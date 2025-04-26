#include "game.hpp"
#include "camera.hpp"
#include "entities/player.hpp"
#include "entities/background.hpp"

void Game::init(float width, float height) {

    //TODO: create entities with a file using an AssetLoader
    entity_manager = std::make_unique<EntityManager>();
    entity_manager->add_entity(std::make_shared<Camera>(glm::vec2 {width, height}));
    entity_manager->add_entity(std::make_shared<Background>(width, height));
    entity_manager->add_entity(std::make_shared<Player>());

    entity_manager->init_entities();
}

void Game::quit() {
    entity_manager->destroy_entities();
}

void Game::update() {
    entity_manager->update_entities();
    // entity_manager->update_drawables();
}

void Game::render(Renderer& renderer) {
    //TODO: render only a specific scene
    renderer.render(entity_manager->get_drawables());
}
