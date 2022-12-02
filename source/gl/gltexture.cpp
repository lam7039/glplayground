#include "gl.hpp"
#include "draw.hpp"

static GLTexture texture;

void Texture::init(vector2i size, const void *data, bool hasAlpha) {
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int mode = hasAlpha ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, mode, size.x, size.y, 0, mode, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture.id);
}

void Texture::free() {
    glDeleteTextures(1, &texture.id);
}
