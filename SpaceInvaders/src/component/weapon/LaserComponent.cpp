#include "component/weapon/LaserComponent.h"
#include "framework/Core.h"
#include "projectile/LaserBeam.h"
#include "framework/World.h"

namespace Nonsense
{

ULaserComponent::ULaserComponent(AActor *owner, float attackRate)
    : UWeaponComponent{owner},
    mCooldownClock{},
    mAttackRate{attackRate}
{

}

bool ULaserComponent::CanAttack() const
{
    return true;
}

bool ULaserComponent::IsOnCooldown() const
{
    return mCooldownClock.getElapsedTime().asSeconds() < mAttackRate;
}

void ULaserComponent::AttackImpl()
{
    mCooldownClock.restart();
    TWeakPtr<ALaserBeam> laserBeam = GetOwner()->GetCurrentWorld()->SpawnActor<ALaserBeam>(GetOwner());
    laserBeam.lock()->SetActorLocation(GetOwner()->GetActorLocation());
    laserBeam.lock()->SetActorRotation(GetOwner()->GetActorRotation());
}

} // namespace Nonsense