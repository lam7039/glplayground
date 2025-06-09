#pragma once

#include "mesh.hpp"
#include "material.hpp"

#include <string>
#include <memory>

//TODO: Model consists of a Geometric shape, Mesh, Skeleton and a Material, a Material consists of Textures and other properties
//TODO: unify Model and Sprite with a Renderable class, Renderable is for Asset/Data (Geometry, Material, etc.), Drawable is for Scene/Entity (Visibility)

class Model {
public:
    Model(std::string_view path);
    ~Model();

    void add_mesh(Mesh& mesh, Material& material);
    const std::vector<std::shared_ptr<Mesh>>& get_meshes() const;
private:
    std::string path;
    std::vector<std::shared_ptr<Mesh>> meshes;
};
