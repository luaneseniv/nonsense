#include "spaceship/Spaceship.h"

namespace Nonsense
{

ASpaceship::ASpaceship(UWorld *owningWorld, const FString& texturePath)
    : AActor{owningWorld, texturePath},
    mVelocity{},
    mSpeed{200.0f}
{

}

void ASpaceship::Tick(float deltaTime)
{
    AActor::Tick(deltaTime);

    AddActorLocationOffset(GetVelocity() * deltaTime);
}

void ASpaceship::SetVelocity(const sf::Vector2f& newVelocity)
{
    mVelocity = newVelocity;
}

void ASpaceship::SetSpeed(float newSpeed)
{
    mSpeed = newSpeed;
}


} // namespace Nonsense