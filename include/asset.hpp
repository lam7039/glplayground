#pragma once

enum AssetType {
    IMAGE,
    SOUND,
    SHADER,
    FONT
};

class AssetInterface {
public:
    virtual void bind() = 0;
    virtual void destroy() = 0;
};

class Asset : public AssetInterface {
public:
    unsigned int get_id() const;
    unsigned int get_reference_count() const;

    void add_reference();
    void remove_reference();
protected:
    AssetType type;
    unsigned int id {0};
    unsigned int reference_count {0};
};
