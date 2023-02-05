#include "assets.hpp"
#include <filesystem>
#include <iostream>

Asset::Asset(const std::string &name, AssetType type) : name(name), type(type) {}

void Asset::bind() {}
void Asset::bind(int index) {}

AssetLoader::AssetLoader() {
    //TODO: current_path annoyingly gets the path from the current active file in the editor for some reason
    workspace = std::string(std::filesystem::current_path()) + "/../";
    std::cout << "Current workspace: " << workspace << std::endl;
}

Asset *AssetLoader::loadTexture(const std::string &name, const std::string &path) {
    assets[name] = new Texture(name, workspace + path, true);
    return assets[name];
}

Asset *AssetLoader::loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath) {
    assets[name] = new Shader(name, workspace + vertexPath, workspace + fragmentPath);
    return assets[name];
}

template <typename T>
T *AssetLoader::find(const std::string &name) {
    return static_cast<T*>(assets[name]);
}

void AssetLoader::bind() {
    find<Shader>("main")->bind();
    find<Texture>("image")->bind(0);
    find<Texture>("mario")->bind(1);
}

void AssetLoader::quit() {
    for (auto asset : assets) {
        if (asset.second->type == IMAGE) {
            static_cast<Texture*>(asset.second)->destroy();
        }
    }
    assets.clear();
}
