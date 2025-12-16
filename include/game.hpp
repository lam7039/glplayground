#pragma once

#include "systems/camera.hpp"
#include "systems/render.hpp"
#include "renderer.hpp"
#include "scene.hpp"

class Game {
public:
    Game(std::string_view workspace, Renderer& renderer);
    void init(glm::vec2 viewport);
    void quit();

    void update();
    void render();
    entt::registry& registry();
private:
    Renderer& renderer;
    CameraSystem camera_system;
    RenderSystem render_system;

    std::shared_ptr<AssetManager> asset_manager;
    std::shared_ptr<Scene> scene;
};
