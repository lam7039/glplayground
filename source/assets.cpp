#include "assets.hpp"
#include "sdl.hpp"
#include <iostream>
#include <filesystem>

AssetLoader::AssetLoader() {
    sdlimage.init();
}

void AssetLoader::load(std::string name, std::string path, AssetType type) {
    assets[name] = {type, name, path, sdlimage.loadSurface(sdlimage.workspace + path)};
}

void AssetLoader::loadAll() {
    std::string path = sdlimage.workspace + "assets";
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        std::string filename = std::filesystem::path(entry.path()).stem();
        std::cout << entry.path() << std::endl << filename << std::endl;
        assets[filename] = {AssetType::IMAGE, filename, entry.path(), sdlimage.loadSurface(entry.path())};
    }
}

void AssetLoader::free(std::string name) {
    sdlimage.freeSurface(assets[name].surface);
}

Asset AssetLoader::find(std::string name) {
    return assets[name];
}

void AssetLoader::quit() {
    assets.clear();
    sdlimage.quit();
}

std::string AssetLoader::getWorkspace() const {
    return sdlimage.workspace;
}
