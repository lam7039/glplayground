#pragma once

#include "entity.hpp"
#include "model.hpp"
#include "assets.hpp"

#include <glm/glm.hpp>

class Renderer {
public:
    Renderer();

    void loadMeshData(const Entity &entity);

    void init(glm::vec2 windowSize);
    void drawMesh(const std::unique_ptr<Mesh> &mesh);
    void draw(Model &model);
    
    void clearColor(glm::vec4 color = {0.2f, 0.2f, 0.2f, 1.0f});
    void clear();
private:
    std::shared_ptr<Shader> shader;

    // shader program, texture, material, mesh, render state (blend/depth), render layer (fore/background), z-order/depth, lighting, object type/category
    // std::unordered_map<std::string, std::vector<std::unique_ptr>> batchQueue;
};
