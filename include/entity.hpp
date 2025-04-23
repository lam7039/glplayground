#pragma once

#include "rectangle.hpp"

#include <glm/glm.hpp>
#include <unordered_map>

class EntityInterface {
public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void destroy() = 0;
    virtual ~EntityInterface() = default;
};

class Entity : public EntityInterface {
public:
    void init() override = 0;
    void update() override = 0;
    void destroy() override = 0;

    void set_id(unsigned int identifier);
    void transform(glm::vec3 &position, glm::vec3 &size);
    void set_position(float x, float y, float z);
    void set_size(float x, float y, float z);

    unsigned int &getId();
    glm::vec3 &getPosition();
    glm::vec3 &getSize();
    // Mesh &getMesh();

protected:
    // Rectangle rectangle;
    glm::vec3 position {0.0f, 0.0f, 0.0f};
    glm::vec3 size {1.0f, 1.0f, 1.0f};

private:
    unsigned int identifier;
};

using EntityMapAlias = std::unordered_map<unsigned int, std::shared_ptr<Entity>>;
