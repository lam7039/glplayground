#include "object.hpp"

void Object::init(vector2i size, const void *data, bool hasAlpha) {
    shader.init();
    texture.init(size, data, hasAlpha);
    vertexArrays.init();
}

void Object::draw() {
    shader.use();
    texture.bind();
    vertexArrays.draw();
}

void Object::free() {
    texture.free();
}
