#pragma once

#include "renderer.hpp"
#include "entity_manager.hpp"
#include "asset_manager.hpp"

class Game {
public:
    Game(const std::string& workspace, Renderer& renderer);
    void init(glm::vec2 viewport);
    void quit();

    void update();
    void render();
private:
    Renderer& renderer;
    std::shared_ptr<AssetManager> asset_manager;
    std::unique_ptr<EntityManager> entity_manager;
};
