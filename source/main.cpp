#include "sdl.hpp"
#include "draw.hpp"
#include "object.hpp"
#include <iostream>

int main(int argc, char **argv) {
    LibSDL sdllib;
    ImageSDL sdlimage;
    Context context;

    sdllib.init();
    sdlimage.init();
    
    Window *window = sdllib.createWindow("Gamedev practice");
    context.init(window->position, window->size, sdllib.getOpenGLFuncName());
    Object object(sdlimage.workspace);

    Surface *surface = sdlimage.loadSurface("assets/image.jpg");
    if (!surface) {
        return 1;
    }
    object.init(surface->size, surface->pixels, surface->hasAlpha);
    sdlimage.freeSurface(surface);

    while (window->running) {
        // sdl.pollEvents();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                window->running = false;
                break;
            }
        }
        
        context.clear();
        object.draw();
        sdllib.swapWindow(window);
    }

    object.destroy();
    sdllib.destroyWindow(window);
    sdlimage.quit();
    sdllib.quit();
    return 0;
}
