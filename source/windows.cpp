#include "windows.hpp"

WindowManager::WindowManager() {
    sdllib.init();
    glFunc = sdllib.getOpenGLFunc();
}

void WindowManager::add(std::string title, vector2i size, vector2i position) {
    Window *window = sdllib.createWindow(title, size, position);
    context.init(window->position, window->size, glFunc);
    windows.push_back(window);
}

Window *WindowManager::find(unsigned int i) {
    return windows[i];
}

void WindowManager::remove() {
    sdllib.destroyWindow(windows.back());
    windows.pop_back();
}

void WindowManager::quit() {
    for (int i = 0; i < windows.size(); i++) {
        remove();
    }

    sdllib.quit();
}

void WindowManager::pollEvents() {
    for (int i = 0; i < windows.size(); i++) {
        sdllib.pollEvents(windows[i]);
    }
}

void WindowManager::clearContext() {
    context.clear();
}

void WindowManager::swap() {
    for (int i = 0; i < windows.size(); i++) {
        sdllib.swapWindow(windows[i]);
    }
}

// void WindowManager::update() {
//     for (int i = 0; i < windows.size(); i++) {
        
//     }
// }

// void WindowManager::render() {
//     context.clear();
//     for (int i = 0; i < windows.size(); i++) {

//         sdllib.swapWindow(windows[i]);        
//     }
// }
