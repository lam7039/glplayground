#include "assets.hpp"
#include "sdl.hpp"
#include <iostream>
#include <filesystem>

AssetLoader::AssetLoader() {
    sdlimage.init();
}

Asset *AssetLoader::load(Asset asset) {
    asset.surface = sdlimage.loadSurface(sdlimage.workspace + asset.path);
    assets[asset.name] = &asset;
    return assets[asset.name];
}

void AssetLoader::loadAll() {
    std::string path = sdlimage.workspace + "assets";
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::string filename = std::filesystem::path(entry.path()).stem();
        std::cout << entry.path() << std::endl << filename << std::endl;
        Asset asset = {filename, entry.path()};
        asset.surface = sdlimage.loadSurface(entry.path());
        assets[filename] = &asset;
    }
}

Asset *AssetLoader::find(std::string name) {
    return assets[name];
}

void AssetLoader::quit() {
    assets.clear();
    sdlimage.quit();
}

std::string AssetLoader::getWorkspace() const {
    return sdlimage.workspace;
}
