#include "gl/gl.hpp"
#include "texture.hpp"

#include "stb/stb_image.h"

Texture::Texture(std::string_view source, bool mipmap) : source(std::string(source)), mipmap(mipmap) {}

void Texture::load() {
    int width, height, channels_in_file;
    unsigned char* pixels = stbi_load(source.c_str(), &width, &height, &channels_in_file, 0);
    
    if (!pixels) {
        std::cout << "Failed to load texture at path: " << source << std::endl;
    }
    
    // CHECK_GL_ERROR(glCreateTextures(GL_TEXTURE_2D, 1, &id));

    CHECK_GL_ERROR(glGenTextures(1, &id));
    CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, id));

    CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    // float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
    // CHECK_GL_ERROR(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));

    // CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    int mode = channels_in_file == 4 ? GL_RGBA : GL_RGB;
    CHECK_GL_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, pixels));

    if (mipmap) {
        CHECK_GL_ERROR(glGenerateMipmap(GL_TEXTURE_2D));
    }

    if (pixels) {
        stbi_image_free(pixels);
    }
}

void Texture::bind() {
    // CHECK_GL_ERROR(glActiveTexture(GL_TEXTURE0 + slot));
    CHECK_GL_ERROR(glActiveTexture(GL_TEXTURE0));
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
