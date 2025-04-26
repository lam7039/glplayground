#pragma once

#include "mesh.hpp"
#include "rectangle.hpp"

#include <memory>
#include <unordered_map>

class DrawableInterface {
public:
    //TODO: draw method is useless bedcause I draw all entities in renderer? perhaps keep it for now to see if there's something in the future I can do with it
    virtual void draw() = 0;
    virtual ~DrawableInterface() = default;
};

class Drawable : public DrawableInterface {
public:
    // void set_mesh(Mesh *mesh); //TODO: implement this if necessary
    const std::shared_ptr<Mesh>& get_mesh() const;
protected:
    std::unique_ptr<Rectangle> rectangle;
    std::string asset;
};

using DrawableMapAlias = std::unordered_map<unsigned int, std::shared_ptr<Drawable>>;
