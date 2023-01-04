#include "windows.hpp"
#include "assets.hpp"
#include "object.hpp"
#include <iostream>

int main(int argc, char **argv) {
    WindowManager windowmanager;
    windowmanager.add("Gamedev practice");
    windowmanager.add("Gamedev practice 2");
    windowmanager.add("Gamedev practice 3");

    AssetLoader assetloader;
    assetloader.load({"image", "assets/image.jpg"});

    Object object(assetloader.getWorkspace());
    Asset *asset = assetloader.find("image");
    object.init(asset->surface->size, asset->surface->pixels, asset->surface->hasAlpha);
    assetloader.free("image");

    while (windowmanager.find(0)->running) {
        for (int i = 0; i < windowmanager.windowCount(); i++) {
            windowmanager.setCurrent(i);
            windowmanager.pollEvents(i);
            
            windowmanager.clearContext();
            object.draw();
            windowmanager.swap(i);
        }
    }

    object.destroy();

    assetloader.quit();
    windowmanager.quit();
    return 0;
}
