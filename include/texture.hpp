#pragma once

#include <string>

class Texture {
public:
    Texture(std::string_view source, bool mipmap = false);

    void load();
    void bind();
    void bind(int index);
    void destroy();
private:
    bool mipmap;
    unsigned int id {0};
    unsigned int slot {0};
    std::string source;
};
