#pragma once

#include "rectangle.hpp"
#include "renderer.hpp"

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

class EntityManager {
public:
    void add(std::shared_ptr<Entity> entity, bool drawable = false);
    void init();
    void update();
    void draw();
    void destroy();

    std::vector<std::shared_ptr<Entity>> &getEntities() const;
    std::vector<std::shared_ptr<DrawableEntity>> &getDrawables() const;
private:
    Renderer renderer;
};
