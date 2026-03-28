#include "player/PlayerSpaceship.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "component/weapon/LaserComponent.h"


namespace Nonsense
{
APlayerSpaceship::APlayerSpaceship(UWorld* owningWorld, const FString& texturePath)
    : ASpaceship{owningWorld, texturePath},
    mMovementInput{},
    // mWeapon{ new ULaserComponent{this, 0.15f} }
    mWeaponComponent{ MakeUniquePtr<ULaserComponent>(this, 0.15f) }
{

}

APlayerSpaceship::~APlayerSpaceship()
{

}

void APlayerSpaceship::Tick(float deltaTime)
{
    
    // Movement updating will be happened in the base class
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

    ClampInput();
    NormalizeVector<sf::Vector2f>(mMovementInput);

    ///////////////////////
    // Attack
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        Attack();
    }
}

void APlayerSpaceship::ConsumeInput()
{
    SetVelocity(mMovementInput * GetSpeed());
}

void APlayerSpaceship::ClampInput()
{
    if (GetActorLocation().y <= 0.0f && mMovementInput.y < 0.0f)
    {
        mMovementInput.y = 0.0f;
    }
    if (GetActorLocation().y >= GetCurrentWorld()->GetWindowSize().y && mMovementInput.y > 0.0f)
    {
        mMovementInput.y = 0.0f;
    }
    if (GetActorLocation().x <= 0.0f && mMovementInput.x < 0.0f)
    {
        mMovementInput.x = 0.0f;
    }
    if (GetActorLocation().x >= GetCurrentWorld()->GetWindowSize().x && mMovementInput.x > 0.0f)
    {
        mMovementInput.x = 0.0f;
    }
}

void APlayerSpaceship::ResetMovementInput()
{
    mMovementInput.x = 0.0f;
    mMovementInput.y = 0.0f;
}

void APlayerSpaceship::Attack()
{
    if (mWeaponComponent)
    {
        mWeaponComponent->Attack();
    }
}

} // namespace Nonsense
