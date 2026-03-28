#pragma once
#include "framework/Actor.h"

namespace Nonsense
{
class ASpaceship : public AActor
{
public:
    ASpaceship (UWorld* owningWorld, const FString& texturePath = "");
    virtual ~ASpaceship();

    virtual void Tick(float deltaTime) override;
    
    virtual void Attack();
    
protected:
    virtual void BeginPlay() override;
    
private:
    sf::Vector2f mVelocity;
    float mSpeed;

public: // getters setters
    sf::Vector2f GetVelocity() const { return mVelocity; }
    float GetSpeed() const { return mSpeed; }
    
    void SetVelocity(const sf::Vector2f& newVelocity);
    void SetSpeed(float newSpeed);

};


} // namespace Nonsense