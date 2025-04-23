#include "window.hpp"
// #include "imgui.hpp"
#include "game.hpp"
#include "renderer.hpp"
#include "gl/gl_renderer.hpp"

#include <filesystem>

//TODO: code builds with no errors, but doesn't run

int main(int argc, char **argv) {
    std::filesystem::current_path(std::filesystem::path(argv[0]).parent_path().parent_path());

    Window window("glplayground");
    // ImGuiWrapper imgui(window.size());

    Renderer renderer;
    renderer.init(std::make_unique<GLRenderer>());

    Game game;
    game.init(window.size().x, window.size().y);

    // imgui.attach(window.instance());

    while (window.running()) {
        game.update();
        game.render(renderer);

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
