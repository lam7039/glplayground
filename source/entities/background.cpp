#include "entities/background.hpp"

Background::Background(int width, int height) : width(width), height(height) {
    
}

void Background::init() {
    position = glm::vec3 {0.0f};
    size = glm::vec3 {width, height, 0.0f};
    asset = "background";
    rectangle = std::make_unique<Rectangle>(position, size, asset);
}

void Background::update() {

}

void Background::draw() {
    
}

void Background::destroy() {

}
