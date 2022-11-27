#include "libsdl.hpp"
#include "opengl.hpp"

int main(int argc, char **argv) {
    LibSDL sdl;
    Renderer *renderer = new LibGL;

    sdl.init();
    Window *window = sdl.createWindow("Gamedev practice");
    renderer->init(window->position, window->size);

    Shader shader;
    Object object;

    Surface *surface = sdl.loadSurface("../assets/image.jpg");
    Texture texture(surface->size, surface->pixels, surface->bytesPerPixel);
    sdl.freeSurface(surface);

    shader.use();
    shader.setInt("ourTexture", 0);

    // shader.setWireframe();
    while (window->running) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                window->running = false;
                break;
            }
        }
        
        renderer->clear();
        shader.use();
        texture.bind();
        object.draw();
        sdl.swapWindow(window);
    }

    sdl.destroyWindow(window);
    sdl.quit();
    return 0;
}
