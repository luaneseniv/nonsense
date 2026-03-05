#pragma once
#include <SFML/System.hpp>

#include "weapon/AttackComponent.h"

namespace Nonsense
{
class ULaserComponent : public UAttackComponent
{
public:
    ULaserComponent(AActor* owner, float attackRate = 1.0f );
    virtual bool CanAttack() const override;
    virtual bool IsOnCooldown() const override;

private:
    virtual void AttackImpl() override;
    sf::Clock mCooldownClock;
    float mAttackRate;

};

} // namespace Nonsense