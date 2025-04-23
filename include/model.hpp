#pragma once

#include "mesh.hpp"
#include <string>
#include <memory>

class Model {
public:
    Model(const std::string &name);
    ~Model();

    void addMesh(Mesh &mesh);
    const std::vector<std::shared_ptr<Mesh>>& get_meshes() const;
private:
    std::string name;
    std::vector<std::shared_ptr<Mesh>> meshes;
};
