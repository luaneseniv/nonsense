#pragma once
#include "spaceship/Spaceship.h"

namespace Nonsense
{
class UWeaponComponent;

class APlayerSpaceship : public ASpaceship
{
public:
    APlayerSpaceship(UWorld* owningWorld, const FString& texturePath = "SpaceShips/T_SpaceShip_v1.png");
    virtual ~APlayerSpaceship();

    virtual void Tick(float deltaTime) override;

    virtual void Attack() override;

private:
    void HandleInput();
    void ConsumeInput();
    void ClampInput();
    void ResetMovementInput();

private:
    sf::Vector2f mMovementInput;
    TUniquePtr<UWeaponComponent> mWeaponComponent;

};

} // namespace Nonsense