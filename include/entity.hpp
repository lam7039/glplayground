#pragma once

#include "rectangle.hpp"

#include <glm/glm.hpp>

class Entity {
public:
    Entity();
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void destroy() = 0;

    void transform(glm::vec3 &position, glm::vec3 &size);
    void setPosition(float x, float y, float z);
    void setSize(float x, float y, float z);

    glm::vec3 &getPosition();
    glm::vec3 &getSize();
    unsigned int &getIdentifier();

protected:
    glm::vec3 position {0.0f, 0.0f, 0.0f};
    glm::vec3 size {1.0f, 1.0f, 1.0f};
    unsigned int identifier;
};

class DrawableEntity : public Entity {
public:
    DrawableEntity(glm::vec3 position, glm::vec3 size, const std::string &asset);

    void init() override;
    void update() override;
    void destroy() override;
    std::unique_ptr<Mesh> &getMesh();

private:
    Rectangle rectangle;
};

void add_entity(std::shared_ptr<Entity> entity, bool drawable = false);

template <typename T>
void add_entity(glm::vec3 position, glm::vec3 size, std::string asset = "") {
    add_entity(std::make_shared<T>(position, size, asset), !std::empty(asset));
}

void init_entities();
void update_entities();
void render_drawables();
void destroy_entities();
std::vector<std::shared_ptr<DrawableEntity>> &get_drawables();
