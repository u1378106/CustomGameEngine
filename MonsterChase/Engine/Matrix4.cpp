
#include "Matrix4.h"
#include <cmath>
#include "Constants.h"
#include "Log.h"


Matrix4 Matrix4::Zero(0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f);

Matrix4 Matrix4::Identity(1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f);


Matrix4::Matrix4(float vals[16])
{
    memcpy(mVals, vals, 16 * sizeof(float));
}

Matrix4::Matrix4(float v00, float v01, float v02, float v03,
    float v10, float v11, float v12, float v13,
    float v20, float v21, float v22, float v23,
    float v30, float v31, float v32, float v33)
{
    mVals[0] = v00;
    mVals[1] = v10;
    mVals[2] = v20;
    mVals[3] = v30;

    mVals[4] = v01;
    mVals[5] = v11;
    mVals[6] = v21;
    mVals[7] = v31;

    mVals[8] = v02;
    mVals[9] = v12;
    mVals[10] = v22;
    mVals[11] = v32;

    mVals[12] = v03;
    mVals[13] = v13;
    mVals[14] = v23;
    mVals[15] = v33;
}

Matrix4::Matrix4(const Matrix4& other)
{
    memcpy(mVals, other.mVals, 16 * sizeof(float));
}

Matrix4& Matrix4::operator=(const Matrix4& other)
{
    memcpy(mVals, other.mVals, 16 * sizeof(float));
    return *this;
}

bool Matrix4::operator==(const Matrix4& other) const
{
    for (int i = 0; i < 16; i++)
    {
        if (mVals[i] != other.mVals[i])
        {
            return false;
        }
    }
    return true;
}

bool Matrix4::operator!=(const Matrix4& other) const
{
    for (int i = 0; i < 16; i++)
    {
        if (mVals[i] != other.mVals[i])
        {
            return true;
        }
    }
    return false;
}

void Matrix4::SetRows(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4)
{
    mVals[0] = row1[0];
    mVals[4] = row1[1];
    mVals[8] = row1[2];
    mVals[12] = row1[3];

    mVals[1] = row2[0];
    mVals[5] = row2[1];
    mVals[9] = row2[2];
    mVals[13] = row2[3];

    mVals[2] = row3[0];
    mVals[6] = row3[1];
    mVals[10] = row3[2];
    mVals[14] = row3[3];

    mVals[3] = row4[0];
    mVals[7] = row4[1];
    mVals[11] = row4[2];
    mVals[15] = row4[3];
}

void Matrix4::GetRows(Vector4& row1, Vector4& row2, Vector4& row3, Vector4& row4) const
{
    row1[0] = mVals[0];
    row1[1] = mVals[4];
    row1[2] = mVals[8];
    row1[3] = mVals[12];

    row2[0] = mVals[1];
    row2[1] = mVals[5];
    row2[2] = mVals[9];
    row2[3] = mVals[13];

    row3[0] = mVals[2];
    row3[1] = mVals[6];
    row3[2] = mVals[10];
    row3[3] = mVals[14];

    row4[0] = mVals[3];
    row4[1] = mVals[7];
    row4[2] = mVals[11];
    row4[3] = mVals[15];
}

void Matrix4::SetColumns(const Vector4& col1, const Vector4& col2, const Vector4& col3, const Vector4& col4)
{
    mVals[0] = col1[0];
    mVals[1] = col1[1];
    mVals[2] = col1[2];
    mVals[3] = col1[3];

    mVals[4] = col2[0];
    mVals[5] = col2[1];
    mVals[6] = col2[2];
    mVals[7] = col2[3];

    mVals[8] = col3[0];
    mVals[9] = col3[1];
    mVals[10] = col3[2];
    mVals[11] = col3[3];

    mVals[12] = col4[0];
    mVals[13] = col4[1];
    mVals[14] = col4[2];
    mVals[15] = col4[3];
}

void Matrix4::GetColumns(Vector4& col1, Vector4& col2, Vector4& col3, Vector4& col4) const
{
    col1[0] = mVals[0];
    col1[1] = mVals[1];
    col1[2] = mVals[2];
    col1[3] = mVals[3];

    col2[0] = mVals[4];
    col2[1] = mVals[5];
    col2[2] = mVals[6];
    col2[3] = mVals[7];

    col3[0] = mVals[8];
    col3[1] = mVals[9];
    col3[2] = mVals[10];
    col4[3] = mVals[11];

    col4[0] = mVals[12];
    col4[1] = mVals[13];
    col4[2] = mVals[14];
    col4[3] = mVals[15];
}

Matrix4 Matrix4::operator+(const Matrix4& rhs) const
{
    Matrix4 result;
    for (int i = 0; i < 16; i++)
    {
        result.mVals[i] = mVals[i] + rhs.mVals[i];
    }
    return result;
}

Matrix4& Matrix4::operator+=(const Matrix4& rhs)
{
    for (int i = 0; i < 16; i++)
    {
        mVals[i] += rhs.mVals[i];
    }
    return *this;
}

Matrix4 Matrix4::operator-(const Matrix4& rhs) const
{
    Matrix4 result;
    for (int i = 0; i < 16; i++)
    {
        result.mVals[i] = mVals[i] - rhs.mVals[i];
    }
    return result;
}

Matrix4& Matrix4::operator-=(const Matrix4& rhs)
{
    for (int i = 0; i < 16; i++)
    {
        mVals[i] -= rhs.mVals[i];
    }
    return *this;
}

Matrix4 Matrix4::operator-() const
{
    Matrix4 result;
    for (int i = 0; i < 16; i++)
    {
        result.mVals[i] = -mVals[i];
    }
    return result;
}

Matrix4 Matrix4::operator*(const Matrix4& rhs) const
{
    Matrix4 result;
    // Column one
    result.mVals[0] = mVals[0] * rhs.mVals[0] + mVals[4] * rhs.mVals[1] + mVals[8] * rhs.mVals[2] + mVals[12] * rhs.mVals[3];
    result.mVals[1] = mVals[1] * rhs.mVals[0] + mVals[5] * rhs.mVals[1] + mVals[9] * rhs.mVals[2] + mVals[13] * rhs.mVals[3];
    result.mVals[2] = mVals[2] * rhs.mVals[0] + mVals[6] * rhs.mVals[1] + mVals[10] * rhs.mVals[2] + mVals[14] * rhs.mVals[3];
    result.mVals[3] = mVals[3] * rhs.mVals[0] + mVals[7] * rhs.mVals[1] + mVals[11] * rhs.mVals[2] + mVals[15] * rhs.mVals[3];

    // Column 2
    result.mVals[4] = mVals[0] * rhs.mVals[4] + mVals[4] * rhs.mVals[5] + mVals[8] * rhs.mVals[6] + mVals[12] * rhs.mVals[7];
    result.mVals[5] = mVals[1] * rhs.mVals[4] + mVals[5] * rhs.mVals[5] + mVals[9] * rhs.mVals[6] + mVals[13] * rhs.mVals[7];
    result.mVals[6] = mVals[2] * rhs.mVals[4] + mVals[6] * rhs.mVals[5] + mVals[10] * rhs.mVals[6] + mVals[14] * rhs.mVals[7];
    result.mVals[7] = mVals[3] * rhs.mVals[4] + mVals[7] * rhs.mVals[5] + mVals[11] * rhs.mVals[6] + mVals[15] * rhs.mVals[7];

    // Column 3
    result.mVals[8] = mVals[0] * rhs.mVals[8] + mVals[4] * rhs.mVals[9] + mVals[8] * rhs.mVals[10] + mVals[12] * rhs.mVals[11];
    result.mVals[9] = mVals[1] * rhs.mVals[8] + mVals[5] * rhs.mVals[9] + mVals[9] * rhs.mVals[10] + mVals[13] * rhs.mVals[11];
    result.mVals[10] = mVals[2] * rhs.mVals[8] + mVals[6] * rhs.mVals[9] + mVals[10] * rhs.mVals[10] + mVals[14] * rhs.mVals[11];
    result.mVals[11] = mVals[3] * rhs.mVals[8] + mVals[7] * rhs.mVals[9] + mVals[11] * rhs.mVals[10] + mVals[15] * rhs.mVals[11];

    // Column 4
    result.mVals[12] = mVals[0] * rhs.mVals[12] + mVals[4] * rhs.mVals[13] + mVals[8] * rhs.mVals[14] + mVals[12] * rhs.mVals[15];
    result.mVals[13] = mVals[1] * rhs.mVals[12] + mVals[5] * rhs.mVals[13] + mVals[9] * rhs.mVals[14] + mVals[13] * rhs.mVals[15];
    result.mVals[14] = mVals[2] * rhs.mVals[12] + mVals[6] * rhs.mVals[13] + mVals[10] * rhs.mVals[14] + mVals[14] * rhs.mVals[15];
    result.mVals[15] = mVals[3] * rhs.mVals[12] + mVals[7] * rhs.mVals[13] + mVals[11] * rhs.mVals[14] + mVals[15] * rhs.mVals[15];

    return result;
}

Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
    Matrix4 result = *this * rhs;
    for (int i = 0; i < 16; i++)
    {
        mVals[i] = result.mVals[i];
    }
    return *this;
}

Vector4 Matrix4::operator*(const Vector4& rhs) const
{
    return Vector4(mVals[0] * rhs[0] + mVals[4] * rhs[1] + mVals[8] * rhs[2] + mVals[12] * rhs[3],
        mVals[1] * rhs[0] + mVals[5] * rhs[1] + mVals[9] * rhs[2] + mVals[13] * rhs[3],
        mVals[2] * rhs[0] + mVals[6] * rhs[1] + mVals[10] * rhs[2] + mVals[14] * rhs[3],
        mVals[3] * rhs[0] + mVals[7] * rhs[1] + mVals[11] * rhs[2] + mVals[15] * rhs[3]);
}

Vector4 operator*(const Vector4& lhs, const Matrix4& rhs)
{
    return Vector4(lhs[0] * rhs.mVals[0] + lhs[1] * rhs.mVals[1] + lhs[2] * rhs.mVals[2] + lhs[3] * rhs.mVals[3],
        lhs[0] * rhs.mVals[4] + lhs[1] * rhs.mVals[5] + lhs[2] * rhs.mVals[6] + lhs[3] * rhs.mVals[7],
        lhs[0] * rhs.mVals[8] + lhs[1] * rhs.mVals[9] + lhs[2] * rhs.mVals[10] + lhs[3] * rhs.mVals[11],
        lhs[0] * rhs.mVals[12] + lhs[1] * rhs.mVals[13] + lhs[2] * rhs.mVals[14] + lhs[3] * rhs.mVals[15]);
}

Matrix4 Matrix4::operator*(float scalar) const
{
    Matrix4 result;
    for (int i = 0; i < 16; i++)
    {
        result.mVals[i] = mVals[i] * scalar;
    }
    return result;
}

Matrix4& Matrix4::operator*=(float scalar)
{
    for (int i = 0; i < 16; i++)
    {
        mVals[i] *= scalar;
    }
    return *this;
}

Matrix4 operator*(float scalar, const Matrix4& matrix)
{
    return matrix * scalar;
}

void Matrix4::Transpose()
{
    float temp = mVals[1];
    mVals[1] = mVals[4];
    mVals[4] = temp;

    temp = mVals[2];
    mVals[2] = mVals[8];
    mVals[8] = temp;

    temp = mVals[3];
    mVals[3] = mVals[12];
    mVals[12] = temp;

    temp = mVals[6];
    mVals[6] = mVals[9];
    mVals[9] = temp;

    temp = mVals[7];
    mVals[7] = mVals[13];
    mVals[13] = temp;

    temp = mVals[11];
    mVals[11] = mVals[14];
    mVals[14] = temp;
}

Matrix4 Matrix4::Transpose(const Matrix4& matrix)
{
    Matrix4 result;
    result.mVals[0] = matrix.mVals[0];
    result.mVals[1] = matrix.mVals[4];
    result.mVals[2] = matrix.mVals[8];
    result.mVals[3] = matrix.mVals[12];
    result.mVals[4] = matrix.mVals[1];
    result.mVals[5] = matrix.mVals[5];
    result.mVals[6] = matrix.mVals[9];
    result.mVals[7] = matrix.mVals[13];
    result.mVals[8] = matrix.mVals[2];
    result.mVals[9] = matrix.mVals[6];
    result.mVals[10] = matrix.mVals[10];
    result.mVals[11] = matrix.mVals[14];
    result.mVals[12] = matrix.mVals[3];
    result.mVals[13] = matrix.mVals[7];
    result.mVals[14] = matrix.mVals[11];
    result.mVals[15] = matrix.mVals[15];
    return result;
}

void Matrix4::Invert()
{
    const Vector3& col0 = reinterpret_cast<const Vector3&>((*this)[0]);
    const Vector3& col1 = reinterpret_cast<const Vector3&>((*this)[1]);
    const Vector3& col2 = reinterpret_cast<const Vector3&>((*this)[2]);
    const Vector3& col3 = reinterpret_cast<const Vector3&>((*this)[3]);

    const float& x = mVals[3];
    const float& y = mVals[7];
    const float& z = mVals[11];
    const float& w = mVals[15];

    Vector3 s = Vector3::Cross(col0, col1);
    Vector3 t = Vector3::Cross(col2, col3);

   /* Vector3 sSSE = Vector3::CrossProduct(col0, col1);
    Vector3 tSSE = Vector3::CrossProduct(col2, col3);*/

    Vector3 u = col0 * y - col1 * x;
    Vector3 v = col2 * w - col3 * z;

    float determinant = Vector3::Dot(s, v) + Vector3::Dot(t, u);
    if (std::fabsf(determinant) < kEpsilon)
    {
        return;
    }

    float invDet = 1.0f / determinant;

    s *= invDet;
    t *= invDet;
    u *= invDet;
    v *= invDet;

    Vector3 row0 = Vector3::Cross(col1, v) + t * y;
    Vector3 row1 = Vector3::Cross(v, col0) - t * x;
    Vector3 row2 = Vector3::Cross(col3, u) + s * w;
    Vector3 row3 = Vector3::Cross(u, col2) - s * z;

    // Calculate right 4x1 column.
    float colX = -Vector3::Dot(col1, t);
    float colY = Vector3::Dot(col0, t);
    float colZ = -Vector3::Dot(col3, s);
    float colW = Vector3::Dot(col2, s);

    //Testing SSE compiler intrinsics Dot Product
    float colXSSE = -Vector3::dot(col1, t);
    float colYSSE = Vector3::dot(col0, t);
    float colZSSE = -Vector3::dot(col3, s);
    float colWSSE = Vector3::dot(col2, s);

    if (colX == colXSSE && colY == colYSSE && colZ == colZSSE && colW == colWSSE)
    {
        //Engine::Log::I("dot product test passed....");
    }

    // Construct final 4x4 matrix.
    mVals[0] = row0.x;
    mVals[1] = row1.x;
    mVals[2] = row2.x;
    mVals[3] = row3.x;

    mVals[4] = row0.y;
    mVals[5] = row1.y;
    mVals[6] = row2.y;
    mVals[7] = row3.y;

    mVals[8] = row0.z;
    mVals[9] = row1.z;
    mVals[10] = row2.z;
    mVals[11] = row3.z;

    mVals[12] = colX;
    mVals[13] = colY;
    mVals[14] = colZ;
    mVals[15] = colW;
}

/*static*/ Matrix4 Matrix4::Inverse(const Matrix4& matrix)
{
    Matrix4 toInvert = matrix;
    toInvert.Invert();
    return toInvert;
}

Vector3 Matrix4::TransformVector(const Vector3& vector) const
{
    return Vector3(mVals[0] * vector[0] + mVals[4] * vector[1] + mVals[8] * vector[2],
        mVals[1] * vector[0] + mVals[5] * vector[1] + mVals[9] * vector[2],
        mVals[2] * vector[0] + mVals[6] * vector[1] + mVals[10] * vector[2]);
}

Vector3 Matrix4::TransformPoint(const Vector3& point) const
{
    return Vector3(mVals[0] * point[0] + mVals[4] * point[1] + mVals[8] * point[2] + mVals[12],
        mVals[1] * point[0] + mVals[5] * point[1] + mVals[9] * point[2] + mVals[13],
        mVals[2] * point[0] + mVals[6] * point[1] + mVals[10] * point[2] + mVals[14]);
}

/*static*/ Matrix4 Matrix4::MakeTranslate(const Vector3& translation)
{
    return Matrix4(1.0f, 0.0f, 0.0f, translation.x,
        0.0f, 1.0f, 0.0f, translation.y,
        0.0f, 0.0f, 1.0f, translation.z,
        0.0f, 0.0f, 0.0f, 1.0f);
}

/*static*/ Matrix4 Matrix4::MakeRotateX(float rotX)
{
    int cos = static_cast<int>(std::cosf(rotX));
    float sin = round(std::sinf(rotX));
    return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cos, -sin, 0.0f,
        0.0f, sin, cos, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}

/*static*/ Matrix4 Matrix4::MakeRotateY(float rotY)
{
    int cos = static_cast<int>(std::cosf(rotY));
    float sin = round(std::sinf(rotY));
    return Matrix4(cos, 0.0f, sin, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -sin, 0.0f, cos, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}

/*static*/ Matrix4 Matrix4::MakeRotateZ(float rotZ)
{
    int cos = static_cast<int>(std::cosf(rotZ));
    float sin = round(std::sinf(rotZ));
    return Matrix4(cos, -sin, 0.0f, 0.0f,
        sin, cos, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}

/*static*/ Matrix4 Matrix4::MakeScale(const Vector3& scale)
{
    return Matrix4(scale.x, 0.0f, 0.0f, 0.0f,
        0.0f, scale.y, 0.0f, 0.0f,
        0.0f, 0.0f, scale.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}
