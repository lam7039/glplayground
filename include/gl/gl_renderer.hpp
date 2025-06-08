#pragma once

#include "renderer.hpp"

class GLRenderer : public GraphicsApiInterface {
public:
    void init() override;
    void draw_mesh(const Mesh& mesh) override;
    void draw(const Model& model) override;
    
    void set_shader(Shader& shader) override;
    void set_wireframe() override;

    void clear_color(glm::vec4 color = {0.2f, 0.2f, 0.2f, 1.0f}) override;
    void clear() override;
};
