#pragma once

#include <unordered_map>
#include <string>

#include "sdl.hpp"
#include "draw.hpp"

enum AssetType {
    IMAGE,
    SOUND,
    SHADER,
    FONT
};

struct Asset {
    std::string name;
    std::string path;
    AssetType type = AssetType::IMAGE;
    Surface *surface;
};

class AssetLoader {
    SDLimage sdlimage;
    std::unordered_map<std::string, Asset*> assets;
public:
    AssetLoader();

    Asset *load(Asset asset);
    void loadAll();
    Asset *find(std::string name);
    void quit();

    std::string getWorkspace() const;
};
