#include "Matrix4Test.h"
#include <cassert> 
#include "Log.h"
#include "Constants.h"

void Matrix4Test::StartTest()
{
    MultiplyTest();
    MultiplayTranslationTest();
    MultiplyRotationTest();
    MultiplyScaleTest();
    InverseTest();
    TransposeTest();
}


Matrix4 Matrix4Test::MultiplyTest()
{
    Matrix4 result(2513.77002f, 3755.54980f, 4017.55005f, 1623.23999f,
        975.489990f, 4293.63037f, 2481.55981f, 764.820068f,
        2430.76001f, 5526.00000f, 6364.45996f, 2483.15991f,
        634.609985f, 4621.31982f, 4207.90967f, 1077.56006f);

    Matrix4Test::mat2 = Matrix4(6.6f, 10.8f, 8.44f, 12.96f,
        -5.77f, 60.66f, 80.02f, 12.34f,
        12.12f, 15.66f, -20.01f, -1.1f,
        25.45f, 33.87f, 42.24f, 16.66f);

    Matrix4Test::mat1 = Matrix4(4, 6, 17, 91,
        12, 44, 76, 9,
        54, 32, 10, 84,
        19, 55, 43, 12);

    Matrix4Test::mul = Matrix4Test::mat1 * Matrix4Test::mat2;

    if (mul == result)
    {
        Engine::Log::I("Test passed for multiplication");
        assert(Matrix4Test::result);
    }
  
    return Matrix4Test::mul;
}

Vector4 Matrix4Test::MultiplayTranslationTest()
{
    Matrix4 translationMatrix = Matrix4::MakeTranslate(Vector3(8, 16, 32));
    Vector4 position(1.0f);

    Vector4 result = translationMatrix * position;

    if (result.x == 8.0f && result.y == 16.0f && result.z == 32.0f)
    {
        Engine::Log::I("Test passed for multiplication of Vector4 by translation Matrix4");
    }

    return result;
}

void Matrix4Test::MultiplyRotationTest()
{
    Matrix4 rotate90YMatrix = Matrix4::MakeRotateY(kPiOver2);
    Vector4 xAxis = Vector4::UnitX;

    Vector4 result = rotate90YMatrix * xAxis;

    if (result.x == 0.0f && result.y == 0.0f && result.z == -1.0f)
    {
        Engine::Log::I("Test passed for Multiply Rotation with Y-axis");
    }

    Matrix4 rotate90ZMatrix = Matrix4::MakeRotateZ(kPiOver2);
    result = rotate90ZMatrix * xAxis;

    if (result.x == 0.0f && result.y == 1.0f && result.z == 0.0f)
    {
        Engine::Log::I("Test passed for Multiply Rotation with Z-axis");
    }
}

void Matrix4Test::MultiplyScaleTest()
{
    Matrix4 scaleUpMatrix = Matrix4::MakeScale(Vector3(4.0f, 4.0f, 4.0f));
    Vector4 pos(1.0f, 1.0f, 1.0f, 1.0f);

    Vector4 result = scaleUpMatrix * pos;

    if (result.x == 4.0f && result.y == 4.0f && result.z == 4.0f && result.w == 1.0f)
    {
        Engine::Log::I("Scale-Up Test passed for Multiply Vector4 by Scale Matrix4");
    }

    Matrix4 scaleDownMatrix = Matrix4::MakeScale(Vector3(1.8f, 1.8f, 1.8f));
    result = scaleDownMatrix * pos;

    if (result.x == 1.8f && result.y == 1.8f && result.z == 1.8f && result.w == 1.0f)
    {
        Engine::Log::I("Scale-Down Test passed for Multiply Vector4 by Scale Matrix4");
    }
}

void Matrix4Test::InverseTest()
{
    Matrix4 matrix(1, 1, 1, 23,
        0, 3, 1, 10,
        2, 3, 1, 14,
        0, 0, 0, 1);
    Matrix4 inverse = Matrix4::Inverse(matrix);

    Matrix4 otherMatrix(0.0f, -0.5f, 0.5f, -2.0f,
        -0.5f, 0.25f, 0.25f, 5.5f,
        1.5f, 0.25f, -0.75f, -26.5f,
        0.0f, 0.0f, 0.0f, 1.0f);

    if (inverse == otherMatrix)
    {
        Engine::Log::I("Inverse values tested correctly");
    }
    
    Matrix4 result = matrix * inverse;
    //REQUIRE(result == Matrix4::Identity);
    if (result == Matrix4::Identity)
    {
        Engine::Log::I("Inverse test passed");
    }
}

void Matrix4Test::TransposeTest()
{
    Matrix4 input(4, 6, 17, 91,
                  12, 44, 76, 9,
                  54, 32, 10, 84,
                  19, 55, 43, 12);

    Matrix4 result(4, 12, 54, 19,
                   6, 44, 32, 55,
                   17, 76, 10, 43,
                   91, 9, 84, 12);

    if (Matrix4::Transpose(input) == result)
    {
        Engine::Log::I("Test passed for Tranpose of Matrix");
    }
}




