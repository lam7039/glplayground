#include "assets.hpp"
#include "renderer.hpp"
#include "rectangle.hpp"
#include "imgui.hpp"
#include "window.hpp"
#include "camera.hpp"

#include "entity.hpp"

#include <glm/glm.hpp>

#include <filesystem>
#include <iostream>

//TODO: create Entity -> Object and EntityManager classes
//TODO: put position/size/textureID in Entity and use Entity list from EntityManager in imgui class 

int main(int argc, char **argv) {
    std::filesystem::current_path(std::filesystem::path(argv[0]).parent_path().parent_path());
    std::printf("Current workspace: %s\n", get_workspace().c_str());

    Window window("glplayground");
    Renderer renderer;
    window.swap();
    ImGuiWrapper imgui;

    load_asset<Shader>("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    load_asset<Texture>("background", "/assets/image.jpg");
    load_asset<Texture>("mario", "/assets/mario.png");

    Camera camera(window.size());
    renderer.init();
    camera.init();

    DrawableEntity background({50.0f, 250.0f, 0.0f}, {200.0f, 150.0f, 0.0f}, "background");
    DrawableEntity mario({500.0f, 250.0f, 0.0f}, {150.0f, 200.0f, 0.0f}, "mario");

    imgui.attach(window.instance());

    while (window.running()) {
        background.update();
        mario.update();
        camera.update();

        renderer.clear();
        renderer.drawMesh(background.getMesh());
        renderer.drawMesh(mario.getMesh());

        imgui.set(background.getPosition(), mario.getPosition(), camera.getPosition(), background.getSize(), mario.getSize(), camera.getSize());
        imgui.render();

        window.swap();
        window.pollEvents();
    }

    imgui.detach();
    clear_assets();

    mario.destroy();
    background.destroy();

    window.destroy();
    
    return 0;
}
