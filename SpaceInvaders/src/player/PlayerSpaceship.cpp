#include "player/PlayerSpaceship.h"
#include "framework/MathUtility.h"

namespace Nonsense
{
APlayerSpaceship::APlayerSpaceship(UWorld* owningWorld, const FString& texturePath)
    : ASpaceship{owningWorld, texturePath},
    mMovementInput{}
{

}

void APlayerSpaceship::Tick(float deltaTime)
{
    HandleInput();
    ConsumeInput();

    // Movement updating will be happened in the base class
    ASpaceship::Tick(deltaTime);
}

void APlayerSpaceship::HandleInput()
{
    ResetMovementInput();

    // Vertical
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        mMovementInput.y = -1.0f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        mMovementInput.y = 1.0f;
    }

    // Horizontal
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        mMovementInput.x = -1.0f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        mMovementInput.x = 1.0f;
    }

    NormalizeVector(mMovementInput);
}

void APlayerSpaceship::ConsumeInput()
{
    SetVelocity(mMovementInput * GetSpeed());
}

void APlayerSpaceship::ResetMovementInput()
{
    mMovementInput.x = 0.0f;
    mMovementInput.y = 0.0f;
}

} // namespace Nonsense
