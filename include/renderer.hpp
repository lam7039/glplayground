#pragma once

#include <vector>

#include "object.hpp"

class Renderer {

public:
    void add(Object *object);
    void draw();
    void destroy();

protected:
    std::vector<Object*> objects;
};
