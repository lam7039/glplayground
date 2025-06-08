#include "window.hpp"
#include "gl/gl_renderer.hpp"
#include "asset_manager.hpp"
#include "scene.hpp"

#include "renderer.hpp"

int main(int argc, char** argv) {
    Window window("glplayground");

    Renderer renderer;
    renderer.set_renderer(std::make_unique<GLRenderer>());
    renderer.init();

    auto asset_manager = get_asset_manager();
    asset_manager->set_workspace(argv[0]);
    asset_manager->load_shader("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    asset_manager->load_texture("background", "/assets/image.jpg");
    asset_manager->load_texture("mario", "/assets/mario.png");

    auto shader = asset_manager->get_shader("main");
    renderer.set_shader(shader);

    Scene scene(window.size());
    scene.init();

    while (window.running()) {
        scene.update();

        renderer.clear();

        renderer.set_shader(shader);
        renderer.render_scene(scene);

        window.swap();
        window.poll_events();
    }

    scene.destroy();
    shader->destroy();
    renderer.destroy();
    window.destroy();

    return 0;
}

//TODO: fetch third party libraries with cmake instead of saving them in the repo









// #include "window.hpp"
// // #include "imgui.hpp"
// #include "game.hpp"
// #include "renderer.hpp"
// #include "gl/gl_renderer.hpp"

// // TODO: move .hpp to source unless they're for a public API
// int main(int argc, char** argv) {
//     Window window("glplayground");
//     // ImGuiWrapper imgui(window.size());

//     Renderer renderer;
//     renderer.set_renderer(std::make_unique<GLRenderer>());
//     renderer.init();

//     Game game(argv[0], renderer);
//     game.init(window.size());

//     // imgui.attach(window.instance());

//     while (window.running()) {
//         game.update();
//         game.render();

//         // imgui.set(entities);
//         // imgui.render();

//         renderer.clear();

//         window.swap();
//         window.poll_events();
//     }

//     // imgui.detach();

//     renderer.destroy();
//     game.quit();
//     window.destroy();
    
//     return 0;
// }
