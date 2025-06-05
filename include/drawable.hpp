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
    virtual void draw() = 0;
    virtual ~Drawable() = default;
    // void set_mesh(Mesh* mesh); //TODO: implement this if necessary
    const std::weak_ptr<Mesh> get_mesh() const;
    // const std::shared_ptr<Model>& get_model() const;
    // const std::shared_ptr<Sprite>& get_sprite() const;
protected:
    // std::unique_ptr<Rectangle> rectangle;
    std::string asset;
};

using DrawableMapAlias = std::unordered_map<unsigned int, std::unique_ptr<Drawable>>;
