
#pragma once
#include <iomanip>
#include <iostream>
#include <intrin.h>
#include <xmmintrin.h>
#include "Math/Point2D.h"

class Vector3
{
public:
    static Vector3 Zero;
    static Vector3 One;
    static Vector3 UnitX;
    static Vector3 UnitY;
    static Vector3 UnitZ;

    Vector3() = default;
    Vector3(float x, float y, float z);

    // Conversion from Vector2
    Vector3(float x, float y);
    Vector3(const Engine::Point2D& other);

    // Copy
    Vector3(const Vector3& other);
    Vector3& operator=(const Vector3& other);

    // Equality
    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;

    // Accessors
    float& operator[](int i) { return (&x)[i]; }
    float  operator[](int i) const { return (&x)[i]; }

    // Addition and subtraction
    Vector3 operator+(const Vector3& other) const;
    Vector3& operator+=(const Vector3& other);
    Vector3 operator-(const Vector3& other) const;
    Vector3& operator-=(const Vector3& other);
    Vector3 operator-() const;

    // Scalar multiplication
    Vector3 operator*(float scalar) const;
    friend Vector3 operator*(float scalar, const Vector3& vector);
    Vector3& operator*=(float scalar);
    Vector3 operator/(float scalar) const;
    Vector3& operator/=(float scalar);

    // Length
    Vector3& Normalize();
    static Vector3 Normalize(const Vector3& v);

    // Component-wise multiplication
    Vector3 operator*(const Vector3& other) const;

    // Length
    float GetLength() const { return std::sqrtf(x * x + y * y + z * z); }
    float GetLengthSq() const { return (x * x + y * y + z * z); }

    // Scalar/dot and vector/cross products
    static float Dot(const Vector3& lhs, const Vector3& rhs);

    //Compiler Instrinsic Dot Product
    static float dot(const Vector3& i_lhs, const Vector3& i_rhs);


    static float CrossProduct(__m128 a, __m128 b);

    static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};