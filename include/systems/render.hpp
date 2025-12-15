#pragma once

#include "asset_manager.hpp"

class RenderSystem {
public:
    RenderSystem(entt::registry& registry);
    void update();
private:
    entt::registry& registry;
    entt::resource<Shader> shader;
};

void update_sprite(entt::registry& registry);
