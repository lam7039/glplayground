#pragma once

#include "asset_manager.hpp"
#include "mesh.hpp"
#include "rectangle.hpp"

class Scene {
public:
    Scene(const glm::vec2& viewport);

    void init();
    void update();
    void destroy();

    auto get_renderables() const {
        return registry.view<Mesh, entt::resource<Texture>>();
    }
    auto get_transformables() const {
        return registry.view<Mesh, Rectangle>();
    }
private:
    entt::registry registry;
};
