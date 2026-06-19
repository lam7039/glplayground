#pragma once

#include <entt/entt.hpp>

class CameraSystem {
public:
    void init();
    void update(entt::registry& registry);
};
