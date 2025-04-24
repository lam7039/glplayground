#include "assets.hpp"
#include <filesystem>

Asset::Asset(const std::string &name, AssetType type) : type(type) {}

// void Asset::bind(int index) {}

unsigned int Asset::getId() const {
    return id;
}

unsigned int Asset::getReferenceCount() const {
    return referenceCount;
}

void Asset::addReference() {
    referenceCount++;
}

void Asset::removeReference() {
    referenceCount--;
}
