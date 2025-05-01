#include "asset.hpp"

unsigned int Asset::get_id() const {
    return id;
}

unsigned int Asset::get_reference_count() const {
    return reference_count;
}

void Asset::add_reference() {
    reference_count++;
}

void Asset::remove_reference() {
    reference_count--;
}
