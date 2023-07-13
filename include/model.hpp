#pragma once

#include "mesh.hpp"
#include <string>
#include <memory>

class Model {
public:
    Model(const std::string &name);
    ~Model();

    void addMesh(Mesh &mesh);
    const std::vector<std::unique_ptr<Mesh>> &getMeshes() const;
private:
    std::string name;
    std::vector<std::unique_ptr<Mesh>> meshes;
};
