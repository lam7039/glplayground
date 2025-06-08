#pragma once

#include "asset.hpp"

#include <string>

class Texture : public Asset {
public:
    //TODO: std::string_view
    Texture(const std::string& source, bool mipmap = false);

    void load() override;
    void bind() override;
    void bind(int index);
    void destroy() override;
private:
    bool mipmap;
    unsigned int slot {0};
};
