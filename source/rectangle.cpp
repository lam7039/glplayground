#include "rectangle.hpp"

Rectangle::Rectangle() {
    generateVertices({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, 0.0f);
    mesh = std::make_unique<Mesh>(vertices, generateIndices());
}

Rectangle::Rectangle(glm::vec3 &position, glm::vec3 &size, float textureId) {
    generateVertices(position, size, textureId);
    mesh = std::make_unique<Mesh>(vertices, generateIndices());
}

// Rectangle::~Rectangle() {
//     destroy();
// }

void Rectangle::transform(glm::vec3 &position, glm::vec3 &size) {
    vertices[0].position = {position.x, position.y, 0.0f};
    vertices[1].position = {position.x + size.x, position.y, 0.0f};
    vertices[2].position = {position.x + size.x, position.y + size.y, 0.0f};
    vertices[3].position = {position.x, position.y + size.y, 0.0f};
    mesh->bind(vertices);
    vertices.clear();
}

void Rectangle::destroy() {
    vertices.clear();
    mesh->destroy();
    mesh.reset();
}

std::unique_ptr<Mesh> &Rectangle::getMesh() {
    return mesh;
}

void Rectangle::generateVertices(glm::vec3 position, glm::vec3 size, float textureId) {
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
}

std::vector<unsigned int> Rectangle::generateIndices() {
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
