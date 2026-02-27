#include "player/PlayerSpaceship.h"


namespace Nonsense
{
APlayerSpaceship::APlayerSpaceship(UWorld* owningWorld, const FString& texturePath)
    : ASpaceship{owningWorld, texturePath},
    mMovementInput{}
{

}

void APlayerSpaceship::Tick(float deltaTime)
{
    ASpaceship::Tick(deltaTime);

    HandleInput();
    ConsumeInput();

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
