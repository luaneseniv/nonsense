#include "framework/MathUtility.h"
#include <math.h>

namespace Nonsense
{

sf::Vector2f RotationToVector(float rotation)
{
    float rad = Deg2Rad(rotation);
    return sf::Vector2f{std::cos(rad), std::sin(rad)};
}

float Deg2Rad(float degrees)
{
    return degrees * (PI / 180.0f);
}

float Rad2Deg(float radians)
{
    return radians * (180.0f / PI);
}

} // namespace Nonsense

