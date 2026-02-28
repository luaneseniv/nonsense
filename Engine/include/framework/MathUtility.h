#pragma onnce
#include <SFML/Graphics.hpp>


namespace Nonsense
{
    const float PI = 3.14159265359;

    sf::Vector2f RotationToVector (float rotation);
    float Deg2Rad (float degrees);
    float Rad2Deg (float radians);

    template <typename T>
    sf::Vector2<T>& ScaleVector (sf::Vector2<T>& inVec, T scaleValue)
    {
        return inVec = {inVec.x * scaleValue, inVec.y * scaleValue};
    }

    template <typename T>
    sf::Vector2<T>& NormalizeVector (sf::Vector2<T>& inVec)
    {
        float vectorLength = static_cast<sf::Vector2f>(inVec).length();
        if (vectorLength == 0.0f) return inVec;

        ScaleVector(inVec, 1.0f / vectorLength);
        
        return inVec;
    }

} // namespace Nonsense