#pragma once

#include "shader.hpp"

class Material {
public:
    Material(unsigned int shader_id);

    void bind_samplers();
private:
    unsigned int shader_id {0};
    std::string texture;
};
