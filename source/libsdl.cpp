#include "libsdl.hpp"
#include <iostream>

void LibSDL::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 3);
}

void LibSDL::quit() {
    SDL_Quit();
}

Window *LibSDL::createWindow(const std::string &title, vector2i size, vector2i position) {
    Window *window = new Window { true, position, size };
    window->instance = SDL_CreateWindow(title.c_str(), position.x != -1 ? position.x : SDL_WINDOWPOS_CENTERED, position.y != -1 ? position.y : SDL_WINDOWPOS_CENTERED, size.x, size.y, SDL_WINDOW_OPENGL);
    if (window->instance == NULL) {
        std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    window->context = SDL_GL_CreateContext(window->instance);
    return window;
}

void LibSDL::swapWindow(Window *window) {
    SDL_GL_SwapWindow(window->instance);
}

void LibSDL::closeWindow(Window *window) {
    std::cout << "exiting..." << std::endl;
    window->running = false;
}

void LibSDL::deleteWindow(Window *window) {
    SDL_GL_DeleteContext(window->context);
    SDL_DestroyWindow(window->instance);
}

SDL_Surface *LibSDL::loadSurface(const std::string &path) const {
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(path.c_str());
    return surface;
}

void LibSDL::freeSurface(SDL_Surface *surface) {
    SDL_FreeSurface(surface);
}
