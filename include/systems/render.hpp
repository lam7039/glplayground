#pragma once

#include "asset_manager.hpp"

class RenderSystem {
public:
    void init(std::shared_ptr<AssetManager> asset_manager);
    void update(entt::registry& registry);
private:
    entt::resource<Shader> shader;
};
