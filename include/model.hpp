#pragma once

#include "mesh.hpp"
#include <string>

class Model {
public:
    Model(const std::string &name);
    ~Model();

    void addMesh(Mesh *mesh);
    const std::vector<Mesh*> &getMeshes() const;
private:
    std::string name;
    std::vector<Mesh*> meshes;
};
