#include "entities/background.hpp"

Background::Background(int width, int height) {
    size = {width, height, 1.0f};
}

void Background::init() {
    asset = "background";
    rectangle = std::make_unique<Rectangle>(position, size, asset);
}

void Background::update() {
    rectangle->transform(position, size);
}

void Background::draw() {
    
}

void Background::destroy() {
    rectangle->destroy();
}
