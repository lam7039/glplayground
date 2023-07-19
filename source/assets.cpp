#include "assets.hpp"
#include <iostream>

Asset::Asset(const std::string &name, AssetType type) : name(name), type(type) {}

void Asset::bind() {}
void Asset::bind(int index) {}

AssetLoader::AssetLoader(const std::string &workspace) : workspace(workspace) {
    std::cout << "Current workspace: " << this->workspace << std::endl;
}

Texture *AssetLoader::loadTexture(const std::string &name, const std::string &path) {
    assets[name] = std::make_unique<Texture>(name, workspace + path, true);
    return static_cast<Texture*>(assets[name].get());
}

Shader *AssetLoader::loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath) {
    assets[name] = std::make_unique<Shader>(name, workspace + vertexPath, workspace + fragmentPath);
    return static_cast<Shader*>(assets[name].get());
}

std::unordered_map<std::string, std::unique_ptr<Asset>> &AssetLoader::getAll() {
    return assets;
}

template <typename T>
T *AssetLoader::find(const std::string &name) {
    return static_cast<T*>(assets[name].get());
}

void AssetLoader::bind() {
    int i = 0;
    for (auto& [name, asset] : assets) {
        if (asset->type == SHADER) {
            asset->bind();
            continue;
        }
        asset->bind(i);
        i++;
    }
}

void AssetLoader::quit() {
    for (auto& [name, asset] : assets) {
        if (asset->type == IMAGE) {
            static_cast<Texture*>(asset.get())->destroy();
        }
    }
    assets.clear();
}
