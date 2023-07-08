#include "quad.hpp"

Quad::Quad() {
    mesh = new Mesh(generateVertices({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, 0.0f), generateIndices());
}

Quad::Quad(glm::vec3 &position, glm::vec3 &size, float textureId) {
    mesh = new Mesh(generateVertices(position, size, textureId), generateIndices());
}

Quad::~Quad() {
    destroy();
}

void Quad::transform(glm::vec3 &position, glm::vec3 &size) {
    vertices[0].position = {position.x, position.y, 0.0f};
    vertices[1].position = {position.x + size.x, position.y, 0.0f};
    vertices[2].position = {position.x + size.x, position.y + size.y, 0.0f};
    vertices[3].position = {position.x, position.y + size.y, 0.0f};
    mesh->bind(vertices);
    vertices.clear();
}

void Quad::destroy() {
    vertices.clear();
    mesh->destroy();
    delete mesh;
}

Mesh &Quad::getMesh() {
    return *mesh;
}

std::vector<Vertex> Quad::generateVertices(glm::vec3 position, glm::vec3 size, float textureId) {
    vertices.push_back({
        position,
        glm::vec4 {1.0f},
        glm::vec2 {0.0f, 0.0f},
        textureId
    });
    vertices.push_back({
        glm::vec3 {position.x + size.x, position.y, 0.0f},
        glm::vec4 {1.0f},
        glm::vec2 {1.0f, 0.0f},
        textureId
    });
    vertices.push_back({
        position + size,
        glm::vec4 {1.0f},
        glm::vec2 {1.0f, 1.0f},
        textureId
    });
    vertices.push_back({
        glm::vec3 {position.x, position.y + size.y, 0.0f},
        glm::vec4 {1.0f},
        glm::vec2 {0.0f, 1.0f},
        textureId
    });
    return vertices;
}

std::vector<unsigned int> Quad::generateIndices() {
    std::vector<unsigned int> indices(24);
    unsigned int offset = 0;
    for (unsigned int i = 0; i < 24; i += 6) {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 3 + offset;
        indices[i + 4] = 2 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    }
    return indices;
}
