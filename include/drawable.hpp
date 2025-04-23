#pragma once

#include "mesh.hpp"
#include "rectangle.hpp"

#include <memory>
#include <unordered_map>

class IDrawable {
public:
    //TODO: draw method is useless bedcause I draw all entities in renderer? perhaps keep it for now to see if there's something in the future I can do with it
    virtual void draw() = 0;
};

class Drawable : public IDrawable {
public:
    void draw() override = 0;

    // void set_mesh(Mesh *mesh); //TODO: implement this if necessary
    const std::shared_ptr<Mesh>& get_mesh() const;
protected:
    Rectangle rectangle;
    std::string asset;
};

using DrawableMapAlias = std::unordered_map<unsigned int, std::shared_ptr<Drawable>>;
