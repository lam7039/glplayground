#pragma once

#include "model.hpp"
#include "drawable.hpp"
#include "shader.hpp"

#include <glm/glm.hpp>

class GraphicsApiInterface {
public:
    virtual void init() = 0;
    virtual void draw_mesh(const Mesh& mesh) = 0;
    virtual void draw(const Model& model) = 0;
    
    virtual void set_shader(Shader& shader) = 0;
    virtual void set_wireframe() = 0;
    
    virtual void clear_color(glm::vec4 color = {0.2f, 0.2f, 0.2f, 1.0f}) = 0;
    virtual void clear() = 0;
};

class Renderer {
public:
    void init();
    void render(const DrawableMapAlias& drawables);
    void destroy();

    void set_renderer(std::unique_ptr<GraphicsApiInterface> backend); 
    void set_shader(Shader& shader);
    void clear();
private:
    std::unique_ptr<GraphicsApiInterface> api;

    //TODO: figure out what to do with this stuff, probably put this (initially in GraphicsApiInterface) here as a todo or something
    // shader program, texture, material, mesh, render state (blend/depth), render layer (fore/background), z-order/depth, lighting, object type/category
    // std::unordered_map<std::string, std::vector<std::unique_ptr>> batch_queue;
};
