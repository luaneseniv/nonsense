#pragma once
#include "framework/Actor.h"

namespace Nonsense
{
class ASpaceship : public AActor
{
public:
    ASpaceship (UWorld* owningWorld, const FString& texturePath = "");
    virtual void Tick(float deltaTime) override;

    // Velocity
    void SetVelocity(const sf::Vector2f& newVelocity);
    sf::Vector2f GetVelocity() const { return mVelocity; }
    
    // Speed
    void SetSpeed(float newSpeed);
    float GetSpeed() const { return mSpeed; }
    
private:
    sf::Vector2f mVelocity;
    float mSpeed;
};


} // namespace Nonsense