#pragma once

#include "rectangle.hpp"

#include <glm/glm.hpp>

class Entity {
public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void destroy() = 0;

    void transform(glm::vec3 &position, glm::vec3 &size);
    void setPosition(float x, float y, float z);
    void setSize(float x, float y, float z);

    glm::vec3 &getPosition();
    glm::vec3 &getSize();

protected:
    glm::vec3 position {0.0f, 0.0f, 0.0f};
    glm::vec3 size {1.0f, 1.0f, 1.0f};
};

class DrawableEntity : public Entity {
public:
    DrawableEntity();
    DrawableEntity(glm::vec3 position, glm::vec3 size, const std::string &asset);

    void init() override;
    void update() override;
    void destroy() override;
    std::unique_ptr<Mesh> &getMesh();

private:
    Rectangle rectangle;
};
