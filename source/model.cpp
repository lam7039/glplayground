#include "model.hpp"

Model::Model(const std::string& path) : path(path) {

}

Model::~Model() {
    for (auto& mesh : meshes) {
        mesh->destroy();
    }
    meshes.clear();
}

void Model::add_mesh(Mesh& mesh, Material& material) {
    meshes.push_back(std::make_unique<Mesh>(mesh));
}

const std::vector<std::shared_ptr<Mesh>>& Model::get_meshes() const {
    return meshes;
}
