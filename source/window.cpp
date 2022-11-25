#include "window.hpp"
#include <iostream>

Window::Window(const std::string& title, vector2i size, vector2i position): position(position), size(size) {
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

    instance = SDL_CreateWindow(title.c_str(), position.x != -1 ? position.x : SDL_WINDOWPOS_CENTERED, position.y != -1 ? position.y : SDL_WINDOWPOS_CENTERED, size.x, size.y, SDL_WINDOW_OPENGL);
    if (instance == NULL) {
        std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
        return;
    }

    context = SDL_GL_CreateContext(instance);
    std::cout << "running..." << std::endl;
}

bool Window::isRunning() {
    return running;
}

void Window::swap() {
    SDL_GL_SwapWindow(instance);
}

void Window::close() {
    std::cout << "exiting..." << std::endl;
    running = false;
}

void Window::quit() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(instance);
    SDL_Quit();
}
