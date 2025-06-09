#include "model.hpp"

Model::Model(std::string_view path) : path(std::string(path)) {

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
