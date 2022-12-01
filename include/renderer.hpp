#pragma once

#include <vector>

#include "vector2.hpp"
#include "vector3.hpp"

class Renderer {

public:
    virtual void init(vector2i position, vector2i size, vector3f color = vector3f(0.2f, 0.2f, 0.2f)) = 0;
    virtual void clear() = 0;

// protected:
//     std::vector<Object> *objects;
};
