#include "gl.hpp"
#include "sdl.hpp"

static SDLimage sdlimage;

//previous load params: vector2i size, void *data, bool hasAlpha
void Texture::load(std::string path) {
    Surface *surface = sdlimage.loadSurface(sdlimage.workspace + path);

    glCreateTextures(GL_TEXTURE_2D, 1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int mode = surface->hasAlpha ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->size.x, surface->size.y, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    sdlimage.freeSurface(surface);
}

void Texture::bind(int index) {
    glBindTextureUnit(index, textureId);
}

void Texture::destroy() {
    glDeleteTextures(1, &textureId);
}
