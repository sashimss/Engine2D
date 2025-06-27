#ifndef VECTOR2_H
#define VECTOR2_H

#include<cmath>

class Vector2{
    public:
        float x, y;

        Vector2(float x_val, float y_val) : x(x_val), y(y_val) {}
        Vector2() : x(0.0f), y(0.0f) {}

        Vector2 operator+(const Vector2& other) const {
            return Vector2(x+other.x, y+other.y);
        }

        Vector2 operator-(const Vector2& other) const {
            return Vector2(x-other.x, y-other.y);
        }

        Vector2 operator*(float scalar) const {
            return Vector2(x*scalar, y*scalar);
        }

        Vector2 operator/(float scalar) const {
            return Vector2(x/scalar, y/scalar);
        }

        Vector2& operator+=(const Vector2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2& operator-=(const Vector2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vector2& operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vector2& operator/=(float scalar) {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        float Magnitude() const {
            return std::sqrt(x*x + y*y);
        }
        
        void Normalize() {
            x = x/this->Magnitude();
            y = y/this->Magnitude();
        }

        Vector2 Normalized() const {
            return Vector2(x/this->Magnitude(), y/this->Magnitude());
        }

        float Dot(const Vector2& other) const{
            return x*other.x + y*other.y;
        }

};


#endif