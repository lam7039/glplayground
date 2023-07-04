#pragma once

#include "quad.hpp"

class Entity {
public:
    virtual void update() = 0;
};

class Object : public Entity {
public:
    virtual void update() = 0;
    void draw();
protected:
    glm::vec3 position;
    glm::vec3 size;
    unsigned int textureId;
private:
    Quad quad;
};
