#pragma once

#include <glm/glm.hpp>

class Entity {
public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void setPosition(float x, float y, float z) = 0;
    virtual void setSize(float x, float y, float z) = 0;
    virtual glm::vec3 getPosition() = 0;

protected:
    glm::vec3 position {0.0f, 0.0f, 0.0f};
    glm::vec3 size {1.0f, 1.0f, 1.0f};
};

class GameObject : public Entity {
public:
    GameObject();

    virtual void update() = 0;
    void draw();
    void setPosition(float x, float y, float z);
    void setSize(float x, float y, float z);
    glm::vec3 getPosition();
};

class InterfaceObject : public Entity {
public:
    virtual void update() = 0;
    void draw();
};
