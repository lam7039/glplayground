#include "entity_manager.hpp"

void EntityManager::add_entity(std::shared_ptr<Entity> entity) {
    entity->set_id(id);
    entity->init();
    entities[id] = entity;

    if (auto drawable = std::dynamic_pointer_cast<Drawable>(entity)) {
        drawables[id] = drawable;
    }

    id++;
}

void EntityManager::remove_entity(unsigned int id) {
    drawables.erase(id);
    entities.erase(id);
}

void EntityManager::init_entities() {
    for (auto& [id, entity] : entities) {
        entity->init();
    }
}

void EntityManager::update_entities() {
    for (auto& [id, entity] : entities) {
        entity->update();
    }
}

void EntityManager::destroy_entities() {
    for (auto& [id, entity] : entities) {
        entity->destroy();
    }
    entities.clear();
}

void EntityManager::update_drawables() {
    //TODO: clear drawables and load a new list of drawables every time a new scene is loading
}

//TODO: check if I should just pass something like std::vector<Entity*> instead of std::vector<std::shared_ptr<Entity>>
DrawableMapAlias EntityManager::get_drawables() const {
    return drawables;
}
