#include "renderer.hpp"

void Renderer::add(Object *object) {
    objects.push_back(object);
}

void Renderer::draw() {
    for (int i = 0; i < objects.size(); i++) {
        // objects[i]->draw();
    }
}

void Renderer::destroy() {
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->destroy();
    }
}
