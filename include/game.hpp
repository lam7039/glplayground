#pragma once

#include "renderer.hpp"
#include "entity_manager.hpp"

class Game {
public:
    void init(glm::vec2 viewport);
    void quit();

    void update();
    void render(Renderer& renderer);
private:
    std::unique_ptr<EntityManager> entity_manager;
};
