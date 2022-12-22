#pragma once

#include <vector>

#include "vector2.hpp"
#include "vector3.hpp"
#include "object.hpp"

class Renderer {

public:
    void add(Object *object);
    void draw();
    void destroy();

protected:
    std::vector<Object*> objects;
};
