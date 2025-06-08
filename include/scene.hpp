#pragma once

#include "asset_manager.hpp"
#include "mesh.hpp"

class Scene {
public:
    Scene(const glm::vec2& viewport);

    void init();
    void update();
    void destroy();

    auto get_renderables() const {
        return registry.view<Mesh, entt::resource<Texture>>();
    }
private:
    entt::registry registry;
};
