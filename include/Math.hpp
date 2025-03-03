#pragma once

#include <iostream>

struct Vector2f{
    Vector2f()
    :x(0.0f), y(0.0f)
    {}

    Vector2f(float p_x, float p_y)
    :x(p_x), y(p_y)
    {}

    Vector2f operator+(Vector2f p_other);
    Vector2f operator-(Vector2f p_other);
    Vector2f operator*(float p_coeff);
    void operator+=(Vector2f p_other);
    void operator*=(float p_coeff);

    void print(){
        std::cout << x << ", " << y << std::endl;
    }

    float x, y;
};