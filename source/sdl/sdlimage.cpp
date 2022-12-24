#include "sdl.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

const std::string path = SDL_GetBasePath();
std::string SDLimage::workspace = path.substr(0, path.length() - 6);

void SDLimage::init() {
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if ((IMG_Init(flags) & flags) != flags) {
        std::cout << "Failed to initialize SDL2_image: " << IMG_GetError() << std::endl;
        return;
    }
}

void SDLimage::quit() {
    IMG_Quit();
}

Surface *SDLimage::loadSurface(const std::string &path) const {
    const std::string& file = workspace + path;
    SDL_Surface *surface = IMG_Load(file.c_str());
    if (!surface || !surface->pixels) {
        std::cout << "Failed to load texture: \n" << IMG_GetError() << std::endl;
        return nullptr;
    }
    return new Surface {(SDL_Surface*)surface, {surface->w, surface->h}, surface->format->BytesPerPixel == 4, surface->pixels};
}

void SDLimage::freeSurface(Surface *surface) {
    SDL_FreeSurface((SDL_Surface*)surface->surface);
    delete surface;
}
