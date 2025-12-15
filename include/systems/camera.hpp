#pragma once

#include "asset_manager.hpp"

class CameraSystem {
public:
    CameraSystem(entt::registry& registry);
    void update();
private:
    entt::registry& registry;
    entt::resource<Shader> shader;
};

void update_camera(entt::registry& registry);
