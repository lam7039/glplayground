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

int WindowManager::windowCount() {
    return windows.size();
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

// bool WindowManager::running() {
//     for (int i = 0; i < windows.size(); i++) {
//         if (!windows[i]->running) {
//             return false;
//         }
//     }
//     return true;
// }

void WindowManager::setCurrent(int windowId) {
    sdllib.setCurrent(windows[windowId]);
}

void WindowManager::pollEvents(int windowId) {
    sdllib.pollEvents(windows[windowId]);
}

void WindowManager::clearContext() {
    context.clear();
}

void WindowManager::swap(int windowId) {
    sdllib.swapWindow(windows[windowId]);
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
