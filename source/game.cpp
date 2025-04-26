#include "game.hpp"
#include "camera.hpp"
#include "entities/player.hpp"
#include "entities/background.hpp"

void Game::init(glm::vec2 viewport) {

    //TODO: create entities with a file using an AssetLoader
    entity_manager = std::make_unique<EntityManager>();
    entity_manager->add_entity(std::make_shared<Camera>(viewport));
    entity_manager->add_entity(std::make_shared<Background>(viewport.x, viewport.y));
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
