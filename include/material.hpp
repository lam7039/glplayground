#pragma once

#include "shader.hpp"

class Material {
public:
    Material(unsigned int shaderId);
    void bindSamplers();
private:
    unsigned int shaderId {0};
};
