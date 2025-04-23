#include "drawable.hpp"

// void Drawable::draw() {

// }

const std::shared_ptr<Mesh>& Drawable::get_mesh() const {
    return rectangle.get_mesh();
}
