#pragma once

#include "entity.hpp"

#include "mesh.hpp"

// class Renderer {
// public:
//     void init();
//     void quit();

//     void beginBatch();
//     void endBatch();
//     void flush();

//     void drawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
//     void drawQuad(const glm::vec2 &position, const glm::vec2 &size, unsigned int textureId);

//     struct stats {
//         unsigned int drawCount = 0;
//         unsigned int quadCount = 0;
//     };

//     const stats &getStats();
//     void resetStats();
// private:
//     unsigned int vertexArrayObject {0};
//     std::array<Vertex*, 1000> vertexArrays;
// };

class Renderer {
public:
    Renderer();

    void loadMeshData(const Entity &entity);
    void draw(Mesh &mesh);
    
    void clearColor(glm::vec4 color = {0.2f, 0.2f, 0.2f, 1.0f});
    void clear();
private:

};