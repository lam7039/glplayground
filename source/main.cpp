#include "window.hpp"
#include "opengl.hpp"

int main(int argc, char **argv) {
    Window window("Gamedev practice");
    OpenGL opengl(window.pos, window.size);
    Shader shader;

    opengl.init();

    while (window.isRunning()) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                window.close();
                break;
            }
        }
        
        opengl.clear();
        shader.use();
        opengl.draw();
        window.swap();
    }

    window.quit();
    return 0;
}