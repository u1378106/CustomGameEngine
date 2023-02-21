#pragma once

static const float kEpsilon = 1.0e-6f;
static const float kPi = 22.0f/7.0f;
static const float k2Pi = 2.0f * kPi;
static const float kPiOver2 = kPi / 2.0f;
static const float kPiOver4 = kPi / 4.0f;

inline float Sqrt(float val)
{
    return std::sqrtf(val);
}

inline float InvSqrt(float val)
{
    return (1.0f / std::sqrtf(val));
}

inline bool IsZero(float val)
{
    return (std::fabsf(val) < kEpsilon);
}