#pragma once

#include "model.hpp"
#include "drawable.hpp"
#include "assets.hpp" //TODO: remove shader from renderer file

#include <glm/glm.hpp>

class IGraphicsApi {
public:
    virtual void init() = 0;
    virtual void draw_mesh(const std::shared_ptr<Mesh>& mesh) = 0;
    virtual void draw(Model &model) = 0;
    
    virtual void clear_color(glm::vec4 color = {0.2f, 0.2f, 0.2f, 1.0f}) = 0;
    virtual void clear() = 0;
protected:
    //TODO: properties shouldn't be in an interface, figure out where to put shader and batch_queue
    std::shared_ptr<Shader> shader;

    // shader program, texture, material, mesh, render state (blend/depth), render layer (fore/background), z-order/depth, lighting, object type/category
    // std::unordered_map<std::string, std::vector<std::unique_ptr>> batch_queue;
};

class Renderer {
public:
    void init(std::unique_ptr<IGraphicsApi> backend);
    void render(DrawableMapAlias drawables);
    void clear();
    void destroy();
private:
    std::unique_ptr<IGraphicsApi> api;
};
