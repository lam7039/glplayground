#include "assets.hpp"

Asset::Asset(const std::string &name, AssetType type) : name(name), type(type) {}

void Asset::bind() {}
void Asset::bind(int index) {}

AssetLoader::AssetLoader(const std::string &workspace) : workspace(workspace) {
    std::printf("Current workspace: %s\n", workspace.c_str());
}

std::unordered_map<std::string, std::shared_ptr<Asset>> &AssetLoader::getAll() {
    return assets;
}

void AssetLoader::remove(const std::string &name) {
    assets.erase(name);
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
