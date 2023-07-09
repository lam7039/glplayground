#pragma once

#include "entity.hpp"
#include "model.hpp"

class Renderer {
public:
    Renderer();

    void loadMeshData(const Entity &entity);
    void drawMesh(Mesh *mesh);
    void draw(Model &model);
    
    void clearColor(glm::vec4 color = {0.2f, 0.2f, 0.2f, 1.0f});
    void clear();
private:

};
