#include "assets.hpp"
#include "renderer.hpp"
#include "rectangle.hpp"
#include "imgui.hpp"
#include "window.hpp"
#include "camera.hpp"

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

    glm::vec3 positionTextureBackground = {50.0f, 250.0f, 0.0f};
    glm::vec3 positionTextureMario = {500.0f, 250.0f, 0.0f};

    glm::vec3 sizeTextureBackground = {200.0f, 150.0f, 0.0f};
    glm::vec3 sizeTextureMario = {150.0f, 200.0f, 0.0f};

    Rectangle background(positionTextureBackground, sizeTextureBackground, "background");
    Rectangle mario(positionTextureMario, sizeTextureMario, "mario");

    imgui.attach(window.instance());

    while (window.running()) {
        background.transform(positionTextureBackground, sizeTextureBackground);
        mario.transform(positionTextureMario, sizeTextureMario);
        camera.update();

        renderer.clear();

        renderer.drawMesh(background.getMesh());
        renderer.drawMesh(mario.getMesh());

        imgui.set(positionTextureBackground, positionTextureMario, sizeTextureBackground, sizeTextureMario);
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
