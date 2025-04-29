#pragma once

#include "asset.hpp"

#include <string>

class Texture : public Asset {
public:
    Texture(const std::string& path, bool mipmap = false);

    void init() override;
    void bind() override;
    void bind(int index);
    void destroy() override;
private:
    bool mipmap;
    int width, height, nrChannels;
    unsigned char* pixels;
    unsigned int slot {0};
};
