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
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void destroy() = 0;
    virtual ~Entity() = default;

    void set_id(unsigned int identifier);
    void transform(glm::vec3& position, glm::vec3& size);
    void set_position(float x, float y, float z);
    void set_size(float x, float y, float z);

    unsigned int& get_id();
    glm::vec3& get_position();
    glm::vec3& get_size();
protected:
    //TODO: generic geometry to pass what you want in, something like Entity<Rectangle>() or Entity<Cube>();

    // Geometry geometry_visual;
    // Geometry geometry_logic;

    glm::vec3 position {0.0f};
    glm::vec3 size {1.0f};

private:
    unsigned int identifier;
};

using EntityMapAlias = std::unordered_map<unsigned int, std::shared_ptr<Entity>>;
