#pragma once

#include "asset.hpp"

#include <string>

class Texture : public Asset {
public:
    Texture(const std::string &path, bool mipmap = false);

    void bind() override;
    void bind(int index);
    void destroy() override;
private:
    unsigned int slot {0};
};
