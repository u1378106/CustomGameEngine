#include "Vector3.h"

#include "Math/Point2D.h"
#include "Constants.h"


Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
Vector3 Vector3::One(1.0f, 1.0f, 1.0f);
Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{

}

Vector3::Vector3(float x, float y) : x(x), y(y), z(0.0f)
{

}

Vector3::Vector3(const Engine::Point2D& other) : x(other.X()), y(other.Y()), z(0.0f)
{

}

Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z)
{

}

Vector3& Vector3::operator=(const Vector3& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
    if (x == other.x && y == other.y && z == other.z)
    {
        return true;
    }
    else
        return false;
}

bool Vector3::operator!=(const Vector3& other) const
{
    if (x != other.x || y != other.y && z != other.z)
    {
        return true;
    }
    else
        return false;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(float scalar) const
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 operator*(float scalar, const Vector3& vector)
{
    return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

Vector3& Vector3::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3 Vector3::operator/(float scalar) const
{
    scalar = 1.0f / scalar;
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3& Vector3::operator/=(float scalar)
{
    scalar = 1.0f / scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3 Vector3::operator*(const Vector3& other) const
{
    return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3& Vector3::Normalize()
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

/*static*/ Vector3 Vector3::Normalize(const Vector3& v)
{
    Vector3 v2 = v;
    v2.Normalize();
    return v2;
}

/*static*/ float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
{
    return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

//SSE Intrinsi Dot Product Calculation
/*static*/ float Vector3::dot(const Vector3& i_lhs, const Vector3& i_rhs)
{
    __m128 vec0 = { i_lhs.x, i_lhs.y, i_lhs.z, 0.0f };
    __m128 vec1 = { i_rhs.x, i_rhs.y, i_rhs.z, 0.0f };

    // do the dot product of the first 3 components – the 7 part of 0x71
    // output result to only lower float of output  - the 1 part of 0x71
    __m128 vec2 = _mm_dp_ps(vec0, vec1, 0x71);

    float dot = _mm_cvtss_f32(vec2);

    return dot;
}

//SSE Intrinsi Cross Product Calculation
 float Vector3::CrossProduct(__m128 a, __m128 b)
{
     __m128 mm_sub_ps = _mm_sub_ps(
        _mm_mul_ps(_mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 1, 0, 2))),
        _mm_mul_ps(_mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1)))
    );
     float result = 0;
      _mm_storeu_ps(&result, mm_sub_ps);
      return result;
}

/*static*/ Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x);
}