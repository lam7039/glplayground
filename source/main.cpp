#include "window.hpp"
// #include "imgui.hpp"
#include "game.hpp"
#include "renderer.hpp"
#include "gl/gl_renderer.hpp"

//TODO: move .hpp to source unless they're for a public API
int main(int argc, char** argv) {
    Window window("glplayground");
    // ImGuiWrapper imgui(window.size());

    Renderer renderer;
    renderer.set_renderer(std::make_unique<GLRenderer>());
    renderer.init();

    Game game(argv[0], renderer);
    game.init(window.size());

    // imgui.attach(window.instance());

    while (window.running()) {
        game.update();
        game.render();

        // imgui.set(entities);
        // imgui.render();

        renderer.clear();

        window.swap();
        window.poll_events();
    }

    // imgui.detach();

    renderer.destroy();
    game.quit();
    window.destroy();
    
    return 0;
}

//TODO: fetch third party libraries with cmake instead of saving them in the repo