#include "entities/player.hpp"

void Player::init() {
    position = {500.0f, 250.0f, 1.0f};
    size = {150.0f, 200.0f, 1.0f};
    asset = "mario";
    rectangle = std::make_unique<Rectangle>(position, size, asset);
}

void Player::update() {
    rectangle->transform(position, size);
}

void Player::draw() {
    
}

void Player::destroy() {
    rectangle->destroy();
}
