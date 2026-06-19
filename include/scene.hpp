#pragma once

#include "asset_manager.hpp"
#include "mesh.hpp"

class Scene {
public:
    Scene(const glm::vec2& viewport);

    void init();
    void update();
    void destroy();

    entt::registry& get_registry();
private:
    entt::registry registry;
};
