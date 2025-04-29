#pragma once

#include "mesh.hpp"
#include "material.hpp"

#include <string>
#include <memory>

class Model {
public:
    Model(const std::string& path);
    ~Model();

    void add_mesh(Mesh& mesh, Material& material);
    const std::vector<std::shared_ptr<Mesh>>& get_meshes() const;
private:
    std::string path;
    std::vector<std::shared_ptr<Mesh>> meshes;
};
