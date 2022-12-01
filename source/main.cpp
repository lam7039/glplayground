#include "libsdl.hpp"
#include "object.hpp"
#include "gl.hpp"

int main(int argc, char **argv) {
    LibSDL sdl;
    ContextGL context;

    sdl.init();
    Window *window = sdl.createWindow("Gamedev practice");
    context.init(window->position, window->size);

    Object object;

    Surface *surface = sdl.loadSurface("../assets/mario.png");
    object.init(surface->size, surface->pixels, surface->hasAlpha);
    sdl.freeSurface(surface);

    while (window->running) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                window->running = false;
                break;
            }
        }
        
        context.clear();
        object.draw();
        sdl.swapWindow(window);
    }

    object.free();
    sdl.destroyWindow(window);
    sdl.quit();
    return 0;
}
