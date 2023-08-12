#include "entity.hpp"

void Entity::transform(glm::vec3 &position, glm::vec3 &size) {
    this->position = position;
    this->size = size;
}

void Entity::setPosition(float x, float y, float z) {
    position = {x, y, z};
}

void Entity::setSize(float x, float y, float z) {
    size = {x, y, z};
}

glm::vec3 &Entity::getPosition() {
    return position;
}

glm::vec3 &Entity::getSize() {
    return size;
}

DrawableEntity::DrawableEntity(glm::vec3 position, glm::vec3 size, const std::string &asset) : rectangle(position, size, asset) {
    transform(position, size);
}

void DrawableEntity::init() {
    rectangle.transform(position, size);
}

void DrawableEntity::update() {
    rectangle.transform(position, size);
}

void DrawableEntity::destroy() {
    rectangle.destroy();
}

std::unique_ptr<Mesh> &DrawableEntity::getMesh() {
    return rectangle.getMesh();
}

static std::vector<std::shared_ptr<Entity>> entities;
static std::vector<std::shared_ptr<DrawableEntity>> drawables;

void EntityManager::add(std::shared_ptr<Entity> entity, bool isDrawable) {
    if (isDrawable) {
        auto drawable = std::static_pointer_cast<DrawableEntity>(entity);
        drawables.push_back(drawable);
        return;
    }
    entities.push_back(entity);
}

void EntityManager::init() {
    renderer.init();
    for (auto drawable : drawables) {
        drawable->init();
    }
    for (auto entity : entities) {
        entity->init();
    }
}

void EntityManager::update() {
    for (auto drawable : drawables) {
        drawable->update();
    }
    for (auto entity : entities) {
        entity->update();
    }
}

void EntityManager::draw() {
    renderer.clear();
    for (auto drawable : drawables) {
        renderer.drawMesh(drawable->getMesh());
    }
}

void EntityManager::destroy() {
    for (auto entity : entities) {
        entity->destroy();
    }
    for (auto drawable : drawables) {
        drawable->destroy();
    }
}
