#pragma once

#include <string>

class Texture {
public:
    //TODO: std::string_view
    Texture(const std::string& source, bool mipmap = false);

    void load();
    void bind();
    void bind(int index);
    void destroy();
private:
    bool mipmap;
    unsigned int id {0};
    unsigned int slot {0};
    const std::string& source;
};
