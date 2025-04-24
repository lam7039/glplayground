#include "asset_manager.hpp"

std::shared_ptr<Asset> AssetManager::get_asset(const std::string &name) {
    return assets[name];
}

void AssetManager::load_asset(const std::string &name, std::shared_ptr<Asset> asset) {
    assets[name] = asset;
}

void AssetManager::load_shader(const std::string &name, const std::string &vertex, const std::string &fragment) {
    load_asset(name, std::make_shared<Shader>(name, workspace + vertex, workspace + fragment));
}

void AssetManager::load_texture(const std::string &name, const std::string &path) {
    load_asset(name, std::make_shared<Texture>(name, workspace + path, true));
}

void AssetManager::remove_asset(const std::string &name) {
    assets[name]->destroy();
    assets.erase(name);
}

void AssetManager::destroy_assets() {
    for (auto& [name, asset] : assets) {
        asset->destroy();
    }
    assets.clear();
}

const std::string& AssetManager::get_workspace() {
    return workspace;
}

AssetManager& get_asset_manager() {
    static AssetManager instance;
    return instance;
}

//TODO: implement reference counting, aka how many times an object has been loaded, so it doesn't unload an asset if other objects still use it in the scene
//TODO: implement a preventUnload boolean for preventing unloading of a commonly used asset
//TODO: use unique_ptr instead of shared_ptr for resource management
