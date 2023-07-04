#include "quad.hpp"

Quad::Quad() {
    setTexCoords(0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

Quad::Quad(glm::vec3 &position, glm::vec3 &size, float textureId) {
    setTexCoords(position.x, position.y, size.x, size.y, textureId);
}

Quad::~Quad() {
    destroy();
}

void Quad::destroy() {
    vertices.clear();
    vertexArray.clear();
}

void Quad::setTexCoords(float x, float y, float width, float height, float textureId) {
    vertices.push_back({
        glm::vec3 {x, y, 0.0f},
        glm::vec4 {1.0f},
        glm::vec2 {0.0f, 0.0f},
        textureId
    });
    vertices.push_back({
        glm::vec3 {x + width, y, 0.0f},
        glm::vec4 {1.0f},
        glm::vec2 {1.0f, 0.0f},
        textureId
    });
    vertices.push_back({
        glm::vec3 {x + width, y + height, 0.0f},
        glm::vec4 {1.0f},
        glm::vec2 {1.0f, 1.0f},
        textureId
    });
    vertices.push_back({
        glm::vec3 {x, y + height, 0.0f},
        glm::vec4 {1.0f},
        glm::vec2 {0.0f, 1.0f},
        textureId
    });
    vertexArray.init(vertices);
}

void Quad::draw(glm::vec3 &position, glm::vec3 &size, float textureId) {
    setTexCoords(position.x, position.y, size.x, size.y, textureId);
    vertexArray.bind(vertices);
    vertexArray.draw();
    vertices.clear();
}
