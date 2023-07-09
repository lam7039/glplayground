#include "model.hpp"

Model::Model(const std::string &name) : name(name) {}

Model::~Model() {
    for (Mesh *mesh : meshes) {
        mesh->destroy();
        delete mesh;
    }
}

void Model::addMesh(Mesh *mesh) {
    meshes.push_back(mesh);
}

const std::vector<Mesh*> &Model::getMeshes() const {
    return meshes;
}
