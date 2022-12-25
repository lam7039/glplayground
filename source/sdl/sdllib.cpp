#include "sdl.hpp"
#include <SDL2/SDL.h>
#include <iostream>

void SDLlib::init() {
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

void SDLlib::quit() {
    SDL_Quit();
}

Window *SDLlib::createWindow(const std::string &title, vector2i size, vector2i position) {
    Window *window = new Window {true, position, size};
    int x = position.x != -1 ? position.x : SDL_WINDOWPOS_CENTERED;
    int y = position.y != -1 ? position.y : SDL_WINDOWPOS_CENTERED;
    window->window = (void**)SDL_CreateWindow(title.c_str(), x, y, size.x, size.y, SDL_WINDOW_OPENGL);
    if (window->window == NULL) {
        std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    window->context = SDL_GL_CreateContext((SDL_Window*)window->window);
    return window;
}

void **SDLlib::getOpenGLFunc() const {
    return (void**)SDL_GL_GetProcAddress;
}

void SDLlib::swapWindow(Window *window) {
    SDL_GL_SwapWindow((SDL_Window*)window->window);
}

void SDLlib::destroyWindow(Window *window) {
    SDL_GL_DeleteContext(window->context);
    SDL_DestroyWindow((SDL_Window*)window->window);
    delete window;
}

void SDLlib::pollEvents(Window *window) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
            window->running = false;
        }
    }
}
