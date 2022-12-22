#include "object.hpp"

Object::Object(std::string basePath) : basePath(basePath) {}

//TODO: find a better way of getting the base path (load shaders and textures in a loader class maybe)
void Object::init(vector2i size, const void *data, bool hasAlpha) {
    shader.init(basePath + "shaders/vertex.glsl", basePath + "shaders/fragment.glsl");
    texture.init(size, data, hasAlpha);
    vertexArrays.init();
}

void Object::draw() {
    shader.use();
    texture.bind();
    vertexArrays.draw();
}

void Object::destroy() {
    texture.free();
}
