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

void load_shader(const std::string &name, const std::string &vertex, const std::string &fragment) {
    load_asset(name, std::make_shared<Shader>(name, get_workspace() + vertex, get_workspace() + fragment));
}

void load_texture(const std::string &name, const std::string &path) {
    load_asset(name, std::make_shared<Texture>(name, get_workspace() + path, true));
}

void remove_asset(const std::string &name) {
    assets[name]->destroy();
    assets.erase(name);
}

void destroy_assets() {
    for (auto& [name, asset] : assets) {
        asset->destroy();
    }
    assets.clear();
}

const std::string &get_workspace() {
    return workspace;
}
