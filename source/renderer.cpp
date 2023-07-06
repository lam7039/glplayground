#include "renderer.hpp"
#include "mesh.hpp"

// static std::array<Vertex, 4> createQuad(float x, float y, float size, float textureId) {
//     // top right
//     Vertex v0;
//     v0.position = {x + size, y, 0.0f};
//     v0.color = {1.0f, 0.0f, 0.0f, 1.0f};
//     v0.texCoords = {1.0f, 0.0f};
//     v0.textureId = textureId;

//     // bottom right
//     Vertex v1;
//     v1.position = {x + size, y + size, 0.0f};
//     v1.color = {0.0f, 1.0f, 0.0f, 1.0f};
//     v1.texCoords = {1.0f, 1.0f};
//     v1.textureId = textureId;

//     // bottom left
//     Vertex v2;
//     v2.position = {x, y + size, 0.0f};
//     v2.color = {0.0f, 0.0f, 1.0f, 1.0f};
//     v2.texCoords = {0.0f, 1.0f};
//     v2.textureId = textureId;

//     // top left 
//     Vertex v3;
//     v3.position = {x, y, 0.0f};
//     v3.color = {1.0f, 1.0f, 1.0f, 1.0f};
//     v3.texCoords = {0.0f, 0.0f};
//     v3.textureId = textureId;

//     return {v0, v1, v2, v3};
// }

void Renderer::init() {

}

void Renderer::loadMeshData(const Entity &entity) {
    // Mesh mesh()
}

void Renderer::render() {

}