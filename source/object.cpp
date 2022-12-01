#include "object.hpp"
#include "gl.hpp"

Object::Object() : shader(new ShaderGL), texture(new TextureGL), vertexArrays(new VertexArraysGL) {}

void Object::init(vector2i size, const void *data, bool hasAlpha) {
    shader->init();
    texture->init(size, data, hasAlpha);
    vertexArrays->init();
}

void Object::draw() {
    shader->use();
    texture->bind();
    vertexArrays->draw();
}

void Object::free() {
    texture->free();
    delete texture;
    delete shader;
    delete vertexArrays;
}
