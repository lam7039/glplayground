#include "entities/background.hpp"

Background::Background(int width, int height) {
    this->width = width;
    this->height = height;
}

void Background::init() {
    position = glm::vec3 {0.0f};
    size = glm::vec3 {width, height, 0.0f};
    asset = "background";
}

void Background::update() {

}

void Background::draw() {
    
}

void Background::destroy() {

}
