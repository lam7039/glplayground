#include "window.hpp"
#include "gl/gl.hpp"
#include "asset_manager.hpp"
#include "scene.hpp"

int main(int argc, char** argv) {
    Window window("test");
    
    CHECK_GL_ERROR(glEnable(GL_BLEND));
    CHECK_GL_ERROR(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    //TODO: refactor asset manager with EnTT resource manager
    auto asset_manager = get_asset_manager();
    asset_manager->set_workspace(argv[0]);
    asset_manager->load_shader("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    asset_manager->load_texture("background", "/assets/image.jpg");
    asset_manager->load_texture("mario", "/assets/mario.png");

    auto shader = asset_manager->get_shader("main").lock();
    shader->load();
    shader->bind();

    Scene scene(window.size());
    scene.init();

    auto renderables = scene.get_renderables();

    while (window.running()) {
        scene.update();

        CHECK_GL_ERROR(glClearColor(0.2f, 0.2f, 0.2f, 0.2f));
        CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        shader->bind();
        shader->set_image("uTexture", 0);

        renderables.each([](auto& mesh, auto& texture) {
            mesh.bind();
            texture->bind();

            mesh.input_layout_bind();
            CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, nullptr));
            mesh.input_layout_unbind();
        });

        window.swap();
        window.poll_events();
    }

    scene.destroy();
    shader->destroy();
    window.destroy();

    return 0;
}

// //TODO: fetch third party libraries with cmake instead of saving them in the repo









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
