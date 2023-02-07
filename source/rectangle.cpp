#include "rectangle.hpp"

Rectangle::Rectangle() {
    setTexCoords(0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

Rectangle::Rectangle(float x, float y, float width, float height, float textureId) {
    setTexCoords(x, y, width, height, textureId);
}

Rectangle::~Rectangle() {
    vertexArray.clear();
}

void Rectangle::setTexCoords(float x, float y, float width, float height, float textureId) {
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

void Rectangle::draw() {
    vertexArray.bind(vertices);
    vertexArray.draw();
}
