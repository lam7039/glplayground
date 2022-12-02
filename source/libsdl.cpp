#include "libsdl.hpp"
#include <iostream>

void LibSDL::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl;
        return;
    }

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int status = IMG_Init(flags);
    if ((status & flags) != flags) {
        std::cout << "Failed to initialize SDL2_image: " << IMG_GetError() << std::endl;
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
    IMG_Quit();
    SDL_Quit();
}

Window *LibSDL::createWindow(const std::string &title, vector2i size, vector2i position) {
    Window *window = new Window { true, position, size };
    int x = position.x != -1 ? position.x : SDL_WINDOWPOS_CENTERED;
    int y = position.y != -1 ? position.y : SDL_WINDOWPOS_CENTERED;
    window->instance = SDL_CreateWindow(title.c_str(), x, y, size.x, size.y, SDL_WINDOW_OPENGL);
    if (window->instance == NULL) {
        std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    window->context = SDL_GL_CreateContext(window->instance);
    return window;
}

GL_PROC LibSDL::getProc() const {
    return (GL_PROC)SDL_GL_GetProcAddress;
}

void LibSDL::swapWindow(Window *window) {
    SDL_GL_SwapWindow(window->instance);
}

void LibSDL::destroyWindow(Window *window) {
    SDL_GL_DeleteContext(window->context);
    SDL_DestroyWindow(window->instance);
    delete window;
}

Surface *LibSDL::loadSurface(const std::string &path) const {
    const std::string& file = workspace() + path;
    SDL_Surface *surfaceSDL = IMG_Load(file.c_str());
    if (!surfaceSDL || !surfaceSDL->pixels) {
        std::cout << "Failed to load texture: \n" << IMG_GetError() << std::endl;
        return nullptr;
    }
    return new Surface { surfaceSDL, vector2i(surfaceSDL->w, surfaceSDL->h), surfaceSDL->format->BytesPerPixel == 4, surfaceSDL->pixels };
}

void LibSDL::freeSurface(Surface *surface) {
    SDL_FreeSurface(surface->surfaceSDL);
    delete surface;
}

std::string LibSDL::workspace() const {
    std::string path = SDL_GetBasePath();
    return path.substr(0, path.length() - 7);
}