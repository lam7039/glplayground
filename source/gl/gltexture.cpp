#include "gl.hpp"
#include "assets.hpp"
#include <iostream>

#include "stb/stb_image.h"

Texture::Texture(const std::string &name, const std::string &path) : Asset(name, IMAGE) {
    stbi_set_flip_vertically_on_load(1);
    
    int width, height, nrChannels;
    unsigned char *pixels = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int mode = nrChannels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pixels);
}

void Texture::bind(int index) {
    glBindTextureUnit(index, textureId);
}

void Texture::destroy() {
    glDeleteTextures(1, &textureId);
}
