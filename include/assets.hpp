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
    AssetType type;
    std::string name;
    std::string path;
    Surface *surface;
};

class AssetLoader {
    SDLimage sdlimage;
    std::unordered_map<std::string, Asset> assets;
public:
    AssetLoader();

    void load(std::string name, std::string path, AssetType type = AssetType::IMAGE);
    void loadAll();
    void free(std::string name);
    Asset find(std::string name);
    void quit();

    std::string getWorkspace() const;
};
