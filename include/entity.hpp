#pragma once

#include "quad.hpp"

class Entity {
public:
    virtual void update() = 0;
    virtual void setPosition(float x, float y, float z) = 0;
    virtual glm::vec3 getPosition() = 0;

protected:
    unsigned int textureId;
    glm::vec3 position;
    glm::vec3 size;
    Quad quad;
};

class GameObject : public Entity {
public:
    GameObject();

    virtual void update() = 0;
    void draw();
    void setPosition(float x, float y, float z);
    glm::vec3 getPosition();
};

class InterfaceObject : public Entity {
public:
    virtual void update() = 0;
    void draw();
};
