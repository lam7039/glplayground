#include "window.hpp"
#include <iostream>

Window::Window(const std::string& title, int width, int height, int x, int y): pos(vector2i(x, y)), size(vector2i(width, height)) {
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

    instance = SDL_CreateWindow(title.c_str(), pos.x != -1 ? pos.x : SDL_WINDOWPOS_CENTERED, pos.y != -1 ? pos.y : SDL_WINDOWPOS_CENTERED, size.x, size.y, SDL_WINDOW_OPENGL);
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