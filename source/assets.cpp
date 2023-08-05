#include "assets.hpp"
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

//TODO: implement reference counting, aka how many times an object has been loaded, so it doesn't unload an asset if other objects still use it in the scene
//TODO: implement a preventUnload boolean for preventing unloading of a commonly used asset

static const std::string workspace = std::filesystem::current_path();
static std::unordered_map<std::string, std::shared_ptr<Asset>> assets;

std::shared_ptr<Asset> get_asset(const std::string &name) {
    return assets[name];
}

void load_asset(const std::string &name, std::shared_ptr<Asset> asset) {
    assets[name] = asset;
}

void remove_asset(const std::string &name) {
    assets[name]->destroy();
    assets.erase(name);
}

void clear_assets() {
    for (auto& [name, asset] : assets) {
        asset->destroy();
    }
    assets.clear();
}

const std::string &get_workspace() {
    return workspace;
}
