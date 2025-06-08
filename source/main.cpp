#include "window.hpp"
// #include "imgui.hpp"
#include "renderer.hpp"
#include "gl/gl_renderer.hpp"
#include "game.hpp"

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

        renderer.clear();
        game.render();

        // imgui.set(entities);
        // imgui.render();

        window.swap();
        window.poll_events();
    }

    // imgui.detach();
    game.quit();
    renderer.destroy();
    window.destroy();

    return 0;
}

//TODO: fetch third party libraries with cmake instead of saving them in the repo
