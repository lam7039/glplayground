#pragma once

#include "assets.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>

class AssetManager {
public:
    std::shared_ptr<Asset> get_asset(const std::string& name);

    template <typename T>
    std::shared_ptr<T> get_asset(const std::string& name) {
        return std::static_pointer_cast<T>(get_asset(name));
    }

    void load_asset(const std::string& name, std::shared_ptr<Asset> asset);
    void load_shader(const std::string& name, const std::string& vertex, const std::string& fragment);
    void load_texture(const std::string& name, const std::string& path);

    void remove_asset(const std::string& name);
    void destroy_assets();

    const std::string& get_workspace();
private:
    std::unordered_map<std::string, std::shared_ptr<Asset>> assets;
    const std::string workspace = std::filesystem::current_path();
};

std::shared_ptr<AssetManager>& get_asset_manager();
