#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

#include <glm/glm.hpp>

enum AssetType {
    IMAGE,
    SOUND,
    SHADER,
    FONT
};

class Asset {
public:
    const std::string &name;
    AssetType type = AssetType::IMAGE;

    virtual void bind();
    virtual void bind(int index);
    Asset(const std::string &name, AssetType type);

    // virtual void create(const std::string &name, AssetType type);
    // virtual void destroy();
};

class Shader : public Asset {
public:
    Shader(const std::string &name, const std::string &vertexSource = "/shaders/vertex.glsl", const std::string &fragmentSource = "/shaders/fragment.glsl");
    
    void bind() override;
    void setWireframe();

    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setImage(const std::string &name, int *samplers);
    void setMatrix(const std::string &name, const glm::mat4 &matrix);

private:
    unsigned int programId {0};
    unsigned int vertexShader {0};
    unsigned int fragmentShader {0};
    std::unordered_map<std::string, int> uniformLocationCache;

    unsigned int compileShader(unsigned int type, const char *source);
    unsigned int createProgram();

    int getLocation(const std::string &name);
};

class Texture : public Asset {
public:
    Texture(const std::string &name, const std::string &path, bool mipmap = false);

    void bind(int index) override;
    void destroy();

    unsigned int getTextureId() const;
    
private:
    unsigned int textureId {0};
};

class AssetLoader {
public:
    AssetLoader(const std::string &workspace);
    
    template <typename T>
    void load(const std::string &name, const std::string &path) {
        assets[name] = std::make_shared<T>(name, workspace + path, true);
        std::printf("%s - Asset loaded\n", name.c_str());
    }

    template <typename T>
    void load(const std::string &name, const std::string &vertex, const std::string &fragment) {
        assets[name] = std::make_shared<T>(name, workspace + vertex, workspace + fragment);
        std::printf("%s - Shader loaded\n", name.c_str());
    }

    template <typename T>
    std::shared_ptr<T> find(const std::string &name) {
        return std::static_pointer_cast<T>(assets[name]);
    }

    std::unordered_map<std::string, std::shared_ptr<Asset>> &getAll();
    //TODO: use Open Asset Import Library (assimp) to load all assets (maybe keep stbi_image for fast image loading)

    void remove(const std::string &name);
    void bind();
    void quit();
    
private:
    std::string workspace;
    std::unordered_map<std::string, std::shared_ptr<Asset>> assets;
};
