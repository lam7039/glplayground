#include "windows.hpp"

Windows::Windows() {
    sdllib.init();
    sdlimage.init();
    glFuncName = sdllib.getOpenGLFuncName();
    workspace = sdlimage.workspace;
}

void Windows::add(std::string title, vector2i size, vector2i position) {
    Window *window = sdllib.createWindow(title, size, position);
    context.init(window->position, window->size, glFuncName);
    windows.push_back(window);
}

void Windows::remove() {
    sdllib.destroyWindow(windows.back());
    windows.pop_back();
}

void Windows::quit() {
    for (int i = 0; i < windows.size(); i++) {
        remove();
    }

    sdlimage.quit();
    sdllib.quit();
}

void Windows::update() {
    for (int i = 0; i < windows.size(); i++) {
        
    }
}

void Windows::render() {
    context.clear();
    for (int i = 0; i < windows.size(); i++) {

        sdllib.swapWindow(windows[i]);        
    }
}
