#pragma once

#include "renderer.hpp"

class VKRenderer : GraphicsApiInterface {
public:
    void init() override;
    void draw_mesh(const Mesh& mesh) override;
    void draw_sprite(const Rectangle& sprite) override;
    void draw(const Model &model) override;
    
    void clear_color(glm::vec4 color = {0.2f, 0.2f, 0.2f, 1.0f}) override;
    void clear() override;
};
