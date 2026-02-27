#pragma once
#include "spaceship/Spaceship.h"

namespace Nonsense
{
class APlayerSpaceship : public ASpaceship
{
public:
    APlayerSpaceship(UWorld* owningWorld, const FString& texturePath = "");

    virtual void Tick(float deltaTime) override;

private:
    void HandleInput();
    void ConsumeInput();
    void ResetMovementInput();

    sf::Vector2f mMovementInput;

};

} // namespace Nonsense