#include "windows.hpp"
#include "assets.hpp"
#include "object.hpp"

int main(int argc, char **argv) {
    WindowManager windowmanager;
    windowmanager.add("Gamedev practice");

    AssetLoader assetloader;
    assetloader.load("image", "assets/image.jpg");

    Object object(assetloader.getWorkspace());
    Asset asset = assetloader.find("image");
    object.init(asset.surface->size, asset.surface->pixels, asset.surface->hasAlpha);
    assetloader.free("image");

    while (windowmanager.find(0)->running) {
        windowmanager.pollEvents();
        
        windowmanager.clearContext();
        object.draw();
        windowmanager.swap();
    }

    object.destroy();

    assetloader.quit();
    windowmanager.quit();
    return 0;
}
