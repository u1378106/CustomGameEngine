
#pragma once
#include <iostream>

class Vector3;

class Vector4
{
public:
    static Vector4 Zero;
    static Vector4 One;
    static Vector4 UnitX;
    static Vector4 UnitY;
    static Vector4 UnitZ;
    static Vector4 UnitW;

    Vector4() = default;
    Vector4(float x, float y, float z, float w);
    Vector4(float w);

    // Conversion from Vector3.
    Vector4(const Vector3& other, float w = 0.0f);

    // Copy
    Vector4(const Vector4& other);
    Vector4& operator=(const Vector4& other);

    // Equality
    bool operator==(const Vector4& other) const;
    bool operator!=(const Vector4& other) const;

    // Accessors
    float& operator[](int i) { return (&x)[i]; }
    float  operator[](int i) const { return (&x)[i]; }

    // Addition and subtraction
    Vector4 operator+(const Vector4& other) const;
    Vector4& operator+=(const Vector4& other);
    Vector4 operator-(const Vector4& other) const;
    Vector4& operator-=(const Vector4& other);
    Vector4 operator-() const;

    // Scalar multiplication
    Vector4 operator*(float scalar) const;
    friend Vector4 operator*(float scalar, const Vector4& vector);
    Vector4& operator*=(float scalar);
    Vector4 operator/(float scalar) const;
    Vector4& operator/=(float scalar);

    // Component-wise multiplication
    Vector4 operator*(const Vector4& other) const;

    // Scalar and vector products
    static float Dot(const Vector4& lhs, const Vector4& rhs);
    static Vector4 Cross(const Vector4& lhs, const Vector4& rhs);

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;


    // Length
    Vector4& Normalize();
    static Vector4 Normalize(const Vector4& v);

    float GetLength() const { return std::sqrtf(x * x + y * y + z * z); }
    float GetLengthSq() const { return (x * x + y * y + z * z); }
};