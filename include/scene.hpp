#pragma once

#include <entt/entt.hpp>
#include "mesh.hpp"
#include "asset_manager.hpp"

class Scene {
public:
    Scene(const glm::vec2& viewport);

    void init();
    void update();
    void destroy();

    auto get_renderables() {
        return registry.view<Mesh, std::shared_ptr<Texture>>();
    }
private:
    entt::registry registry;
};
