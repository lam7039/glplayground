#include "assets.hpp"
#include <iostream>
#include <filesystem>

Asset::Asset(const std::string &name, AssetType type) : type(type) {}

// void Asset::bind(int index) {}

unsigned int Asset::getId() const {
    return id;
}

unsigned int Asset::getReferenceCount() const {
    return referenceCount;
}

void Asset::addReference() {
    referenceCount++;
}

void Asset::removeReference() {
    referenceCount--;
}

AssetLoader::AssetLoader() : workspace(std::filesystem::current_path()) {
    std::printf("Current workspace: %s\n", workspace.c_str());
    assets = std::unordered_map<std::string, std::shared_ptr<Asset>>();
}

std::unordered_map<std::string, std::shared_ptr<Asset>> &AssetLoader::getAll() {
    return assets;
}

void AssetLoader::remove(const std::string &name) {
    //TODO: implement reference counting, aka how many times an object has been loaded, so it doesn't unload an asset if other objects still use it in the scene
    //TODO: implement a preventUnload boolean for preventing unloading of a commonly used asset
    // if (assets[name]->getReferenceCount() > 0) {
    //     return;
    // }

    if (assets[name]->type == AssetType::IMAGE) {
        textureCount--;
    }
    assets[name]->destroy();
    assets.erase(name);
}

void AssetLoader::bind() {
    // int i = 0;
    for (auto& [name, asset] : assets) {
        // if (assets[name]->type == AssetType::IMAGE) {
        //     asset->bind(i);
        //     i++;
        //     continue;
        // }
        // asset->bind();
    }
}

void AssetLoader::quit() {
    for (auto& [name, asset] : assets) {
        asset->destroy();
    }
    textureCount = 0;
    assets.clear();
}
