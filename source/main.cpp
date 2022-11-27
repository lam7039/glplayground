#include "libsdl.hpp"
#include "opengl.hpp"
#include <iostream>
int main(int argc, char **argv) {
    LibSDL sdl;
    GLContext context;

    sdl.init();
    Window *window = sdl.createWindow("Gamedev practice");
    context.init(window->position, window->size);

    Shader shader;
    Object object;

    shader.setWireframe();
    while (window->running) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                sdl.closeWindow(window);
                break;
            }
        }
        
        context.clear();
        shader.use();
        object.draw();
        sdl.swapWindow(window);
    }

    sdl.deleteWindow(window);
    sdl.quit();
    return 0;
}
