#pragma once

template <typename T>
class vector3 {
public:
    T x, y, z;

    vector3(): x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)) {}
    vector3(T x, T y, T z): x(x), y(y), z(z) {}

    void set(T x, T y, T z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    bool operator == (const vector3<T> &a) {
        return (this->x == a.x && this->y == a.y && this->z == a.z);
    }
    bool operator != (const vector3<T> &a) {
        return (this->x != a.x || this->y != a.y || this->z != a.z);
    }
};

typedef vector3<float> vector3f;
typedef vector3<int> vector3i;
