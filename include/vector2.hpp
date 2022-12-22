#pragma once

template <typename T>
class vector2 {
public:
    T x, y;

    vector2(): x(static_cast<T>(0)), y(static_cast<T>(0)) {}
    vector2(T x, T y): x(x), y(y) {}

    void set(T x, T y) {
        this->x = x;
        this->y = y;
    }

    bool operator == (const vector2<T> &a) {
        return (this->x == a.x && this->y == a.y);
    }
    bool operator != (const vector2<T> &a) {
        return (this->x != a.x || this->y != a.y);
    }
};

typedef vector2<float> vector2f;
typedef vector2<int> vector2i;
