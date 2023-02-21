#pragma once
#include <iostream>

#include "Vector3.h"
#include "Vector4.h"

class Matrix4
{
public:
    static Matrix4 Zero;
    static Matrix4 Identity;

    Matrix4() = default;
    Matrix4(float vals[16]);
    Matrix4(float v00, float v01, float v02, float v03,
        float v10, float v11, float v12, float v13,
        float v20, float v21, float v22, float v23,
        float v30, float v31, float v32, float v33);

    // Copy
    Matrix4(const Matrix4& other);
    Matrix4& operator=(const Matrix4& other);

    // Equality
    bool operator==(const Matrix4& other) const;
    bool operator!=(const Matrix4& other) const;

    // Accessors - get entry using (row, col) notation
    float& operator()(int row, int col) { return mVals[row + 4 * col]; }
    float operator()(int row, int col) const { return mVals[row + 4 * col]; }

    // Accessors - get column using [index] notation
    Vector4& operator[](int col) { return (*reinterpret_cast<Vector4*>(&mVals[col * 4])); }
    const Vector4& operator[](int col) const { return (*reinterpret_cast<const Vector4*>(&mVals[col * 4])); }

    // More explicit Row/Column getters/setters.
    void SetRows(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4);
    void GetRows(Vector4& row1, Vector4& row2, Vector4& row3, Vector4& row4) const;
    void SetColumns(const Vector4& col1, const Vector4& col2, const Vector4& col3, const Vector4& col4);
    void GetColumns(Vector4& col1, Vector4& col2, Vector4& col3, Vector4& col4) const;

    // Implicit float conversion - allows Matrix4 to be passed as a float* argument.
    operator float* () { return mVals; }
    operator const float* () const { return mVals; }

    // Addition and subtraction
    Matrix4 operator+(const Matrix4& rhs) const;
    Matrix4& operator+=(const Matrix4& rhs);
    Matrix4 operator-(const Matrix4& rhs) const;
    Matrix4& operator-=(const Matrix4& rhs);
    Matrix4 operator-() const;

    // Matrix multiplication
    Matrix4 operator*(const Matrix4& rhs) const;
    Matrix4& operator*=(const Matrix4& rhs);

    // Vector4 multiplication - column-vector (rhs) and row-vector (lhs)
    Vector4 operator*(const Vector4& rhs) const;
    friend Vector4 operator*(const Vector4& lhs, const Matrix4& rhs);

    // Scalar multiplication
    Matrix4 operator*(float scalar) const;
    Matrix4& operator*=(float scalar);
    friend Matrix4 operator*(float scalar, const Matrix4& matrix);

    // Transpose
    void Transpose();
    static Matrix4 Transpose(const Matrix4& matrix);

    // Inverse
    void Invert();
    static Matrix4 Inverse(const Matrix4& matrix);
 
    // Transform Functions
    // Extraction of transform data
    const Vector3& GetXAxis() const { return reinterpret_cast<const Vector3&>(mVals[0]); }
    const Vector3& GetYAxis() const { return reinterpret_cast<const Vector3&>(mVals[4]); }
    const Vector3& GetZAxis() const { return reinterpret_cast<const Vector3&>(mVals[8]); }
    const Vector3& GetTranslation() const { return reinterpret_cast<const Vector3&>(mVals[12]); }

    Vector3 TransformVector(const Vector3& vector) const;
    Vector3 TransformPoint(const Vector3& point) const;

    static Matrix4 MakeTranslate(const Vector3& translation);

    static Matrix4 MakeRotateX(float rotX);
    static Matrix4 MakeRotateY(float rotY);
    static Matrix4 MakeRotateZ(float rotZ);

    static Matrix4 MakeScale(const Vector3& scale);

private:
    // The indexes of each matrix element are:
    // | 00 04 08 12 |
    // | 01 05 09 13 |
    // | 02 06 10 14 |
    // | 03 07 11 15 |
    float mVals[16];
};