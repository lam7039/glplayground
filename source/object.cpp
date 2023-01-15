#include "object.hpp"
#include <iostream>

Object::Object(std::string basePath) : basePath(basePath) {}

//TODO: find a better way of getting the base path (load shaders and textures in a loader class maybe)
void Object::init(Asset *asset) {
    shader.init(basePath + "shaders/vertex.glsl", basePath + "shaders/fragment.glsl");
    shader.use();

    vertexArrays.init();
    texture.load(asset->path);
}

void Object::draw(int index) {
    shader.use();
    int samplers[2] = { 0, 1 };
    shader.setImage("ourTextures", samplers);
    texture.bind(index);
    vertexArrays.draw();
}

void Object::destroy() {
    texture.destroy();
}
