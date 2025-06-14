#pragma once

#include "renderer.hpp"

class Game {
public:
    Game(std::string_view workspace, Renderer& renderer);
    void init(glm::vec2 viewport);
    void quit();

    void update();
    void render();
private:
    Renderer& renderer;
    std::shared_ptr<AssetManager> asset_manager;
    std::shared_ptr<Scene> scene;
};
