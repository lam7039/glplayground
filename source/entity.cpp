#include "entity.hpp"

void Object::update() {
    
}

void Object::draw() {
    quad.draw(position, size, textureId);
}
