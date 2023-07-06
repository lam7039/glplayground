#pragma once

#include "entity.hpp"
#include "vertex.hpp"

// struct Vertex {
//     glm::vec3 position;
//     glm::vec4 color;
//     glm::vec2 texCoords;
//     float textureId;
// };

// class VertexArray {
// public:
//     void init();
//     void bind();
//     void draw();
//     void quit();
// };


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
    void init();
    void loadMeshData(const Entity &entity);
    void render();
private:

};