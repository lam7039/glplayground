#pragma once

#include "renderer.hpp"

class GLRenderer : public GraphicsApiInterface {
public:
    void init() override;
    void draw_mesh(const std::shared_ptr<Mesh>& mesh) override;
    void draw(Model &model) override;
    
    void clear_color(glm::vec4 color = {0.2f, 0.2f, 0.2f, 1.0f}) override;
    void clear() override;
};
