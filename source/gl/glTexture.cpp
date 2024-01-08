#include "gl.hpp"
#include "assets.hpp"

// #define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::Texture(const std::string &name, const std::string &path, bool mipmap) : Asset(name, AssetType::IMAGE) {
    stbi_set_flip_vertically_on_load(1);
    
    int width, height, nrChannels;
    unsigned char *pixels = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    
    CHECK_GL_ERROR(glCreateTextures(GL_TEXTURE_2D, 1, &id));
    //TODO: is glBindTexture necessary since glCreateTextures autommatically binds the texture?
    CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, id));

    CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    // float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
    // CHECK_GL_ERROR(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));

    CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    
    int mode = nrChannels == 4 ? GL_RGBA : GL_RGB;
    CHECK_GL_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, pixels));
    if (mipmap) {
        CHECK_GL_ERROR(glGenerateMipmap(GL_TEXTURE_2D));
    }

    stbi_image_free(pixels);
}

void Texture::bind() {
    CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, id));
    // CHECK_GL_ERROR(glBindTextureUnit(0, id));

    // int max_texture_image_units;
    // glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_image_units);
    
    // for (int i = 0; i < max_texture_image_units; i++) {
    //     if (glIsEnabled(GL_TEXTURE_2D)) {
    //         CHECK_GL_ERROR(glBindTextureUnit(max_texture_image_units, id));
    //     }
    // }

}

void Texture::bind(int index) {
    CHECK_GL_ERROR(glBindTextureUnit(index, id));
}

void Texture::destroy() {
    CHECK_GL_ERROR(glDeleteTextures(1, &id));
}
