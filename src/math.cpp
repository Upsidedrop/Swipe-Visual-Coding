#include "Math.hpp"

Vector2f Vector2f::operator+(Vector2f p_other){
    return Vector2f(x + p_other.x, y + p_other.y);
}
Vector2f Vector2f::operator-(Vector2f p_other){
    return Vector2f(x - p_other.x, y - p_other.y);
}
Vector2f Vector2f::operator*(float p_coeff){
    return Vector2f(x * p_coeff, y * p_coeff);
}
void Vector2f::operator+=(Vector2f p_other){
    x += p_other.x;
    y += p_other.y;
}
void Vector2f::operator*=(float p_coeff){
    x *= p_coeff;
    y *= p_coeff;
}