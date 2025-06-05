#pragma once

#include "rectangle.hpp"

#include <glm/glm.hpp>
#include <unordered_map>
#include <typeindex>

class EntityInterface {
public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void destroy() = 0;
    virtual ~EntityInterface() = default;
};

class Entity : public EntityInterface {
public:
    void set_id(unsigned int identifier);

    //transform, set_position, set_size, get_position and get_size will be unnecessary when I use the entity component system to add a rectangle, cube or whatever component necessary
    void transform(glm::vec3& position, glm::vec3& size);
    void set_position(float x, float y, float z);
    void set_size(float x, float y, float z);

    unsigned int get_id() const;
    const glm::vec3& get_position() const;
    const glm::vec3& get_size() const;

protected:
    glm::vec3 position {0.0f};
    glm::vec3 size {1.0f};

private:
    unsigned int identifier;

};
