#include "Vector4.h"

#include "Vector3.h"
#include "Constants.h"

Vector4 Vector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);
Vector4 Vector4::One(1.0f, 1.0f, 1.0f, 1.0f);
Vector4 Vector4::UnitX(1.0f, 0.0f, 0.0f, 0.0f);
Vector4 Vector4::UnitY(0.0f, 1.0f, 0.0f, 0.0f);
Vector4 Vector4::UnitZ(0.0f, 0.0f, 1.0f, 0.0f);
Vector4 Vector4::UnitW(0.0f, 0.0f, 0.0f, 1.0f);

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{

}

Vector4::Vector4(float w) : w(w)
{
//Default Vector4
}

Vector4::Vector4(const Vector3& other, float w) : Vector4(other.x, other.y, other.z, w)
{

}

Vector4::Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w)
{

}

Vector4& Vector4::operator=(const Vector4& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

bool Vector4::operator==(const Vector4& other) const
{
    if (x == other.x && y == other.y && z == other.z && w == other.w)
    {
        return true;
    }
    else
        return false;
}

bool Vector4::operator!=(const Vector4& other) const
{
    if (x != other.x && y != other.y && z != other.z && w != other.w)
    {
        return true;
    }
    else
        return false;
}

Vector4 Vector4::operator+(const Vector4& other) const
{
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4& Vector4::operator+=(const Vector4& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

Vector4 Vector4::operator-(const Vector4& other) const
{
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4& Vector4::operator-=(const Vector4& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

Vector4 Vector4::operator-() const
{
    return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator*(float scalar) const
{
    return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vector4 operator*(float scalar, const Vector4& vector)
{
    return Vector4(vector.x * scalar, vector.y * scalar, vector.z * scalar, vector.w * scalar);
}

Vector4& Vector4::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Vector4 Vector4::operator/(float scalar) const
{
    scalar = 1.0f / scalar;
    return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vector4& Vector4::operator/=(float scalar)
{
    scalar = 1.0f / scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Vector4 Vector4::operator*(const Vector4& other) const
{
    return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

float Vector4::Dot(const Vector4& lhs, const Vector4& rhs)
{
    return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w);
}

Vector4 Vector4::Cross(const Vector4& lhs, const Vector4& rhs)
{
    return Vector4(lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x,
        lhs.w * rhs.w);
}

Vector4& Vector4::Normalize()
{
    float lengthSq = GetLengthSq();
    if (IsZero(lengthSq))
    {
        return *this;
    }

    float oneOverLength = InvSqrt(lengthSq);
    x *= oneOverLength;
    y *= oneOverLength;
    z *= oneOverLength;
    return *this;
}

/*static*/ Vector4 Vector4::Normalize(const Vector4& v)
{
    Vector4 v3 = v;
    v3.Normalize();
    return v3;
}