#pragma once

#include "asset_manager.hpp"
#include "renderer.hpp"

class RenderSystem {
public:
    RenderSystem(Renderer& renderer);
    void init(std::shared_ptr<AssetManager> asset_manager);
    void update(entt::registry& registry);
    void render(entt::registry& registry);
private:
    Renderer& renderer;
    entt::resource<Shader> shader;
};
