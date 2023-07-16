#include "model.hpp"

Model::Model(const std::string &name) : name(name) {}

Model::~Model() {
    for (auto &mesh : meshes) {
        mesh->destroy();
        // mesh.release();
    }
    meshes.clear();
}

void Model::addMesh(Mesh &mesh) {
    meshes.push_back(std::make_unique<Mesh>(mesh));
}

const std::vector<std::unique_ptr<Mesh>> &Model::getMeshes() const {
    return meshes;
}
