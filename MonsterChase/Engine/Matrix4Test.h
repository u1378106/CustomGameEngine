#pragma once

#include "Matrix4.h"

class Matrix4Test
{
public:
     Matrix4 result;
     Matrix4 mul;
     Matrix4 mat1;
     Matrix4 mat2;

     Matrix4 MultiplyTest();
     Vector4 MultiplayTranslationTest();
     void MultiplyRotationTest();
     void MultiplyScaleTest();
     void InverseTest();
     void TransposeTest();

     void StartTest();
};