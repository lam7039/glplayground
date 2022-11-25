#include "window.hpp"
#include "opengl.hpp"

int main(int argc, char **argv) {
    Window window("Gamedev practice");
    GLContext context;
    Shader shader;
    VertexArray vertices;

    context.init(window.position, window.size);
    shader.setWireframe();
    while (window.isRunning()) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                window.close();
                break;
            }
        }
        
        context.clear();
        shader.use();
        vertices.draw();
        window.swap();
    }

    window.quit();
    return 0;
}
