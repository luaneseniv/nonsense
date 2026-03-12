#pragma onnce
#include <SFML/System/Vector2.hpp>
#include <box2d/math_functions.h>



namespace Nonsense
{

    const double PI = 3.14159265359;

    inline float Deg2Rad(float degrees)
    {
        return degrees * (PI / 180.0f);
    }

    inline float Rad2Deg(float radians)
    {
        return radians * (180.0f / PI);
    }

    template <typename Vector2D>
    Vector2D RotationToVector(float rotation)
    {
        float rad = Deg2Rad(rotation);
        return Vector2D{std::cos(rad), std::sin(rad)};
    }

    template <typename Vector2D>
    float GetVectorLengthSqr(const Vector2D& inVec)
    {
        return Vector2D{inVec.x * inVec.x + inVec.y * inVec.y};
    }

    template <typename Vector2D>
    float GetVectorLength(const Vector2D& inVec)
    {
        return std::sqrtf(inVec.x * inVec.x + inVec.y * inVec.y); // doesn't need to be double
    }

    template <typename Vector2D>
    Vector2D& ScaleVector(Vector2D& inVec, float scaleValue)
    {
        return inVec = {inVec.x * scaleValue, inVec.y * scaleValue};
    }

    template <typename Vector2D>
    Vector2D& NormalizeVector(Vector2D& inVec)
    {
        float vectorLength = GetVectorLength<Vector2D>(inVec);
        if (vectorLength < 0.00001f) return inVec;

        ScaleVector<Vector2D>(inVec, 1.0f / vectorLength);
        
        return inVec;
    }

    //////////////// Converter ////////////////////
    
    // Convert to SFML Vector2f
    template <typename T>
    sf::Vector2f ToSfVector2(const T& inVec)
    {
        return {inVec.x, inVec.y};
    }

    // Convert to Box2D b2Vec2
    template <typename T>
    b2Vec2 ToB2Vector2(const T& inVec)
    {
        return {inVec.x, inVec.y};
    }

} // namespace Nonsense