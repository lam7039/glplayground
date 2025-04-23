#pragma once

#include "renderer.hpp"
#include "entity_manager.hpp"

class Game {
public:
    void init(float width, float height);
    void quit();

    void update();
    void render(Renderer& renderer);
private:
    std::unique_ptr<EntityManager> entity_manager;
};
