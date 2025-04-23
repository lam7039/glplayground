#include "entities/player.hpp"

void Player::init() {
    position = glm::vec3 {500.0f, 250.0f, 1.0f};
    size = glm::vec3 {150.0f, 200.0f, 1.0f};
    asset = "mario";
}

void Player::update() {

}

void Player::draw() {
    
}

void Player::destroy() {

}
