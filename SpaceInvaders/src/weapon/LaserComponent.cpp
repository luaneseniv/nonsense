#include "weapon/LaserComponent.h"
#include "framework/Core.h"
#include "projectile/LaserBeam.h"
#include "framework/World.h"

namespace Nonsense
{

ULaserComponent::ULaserComponent(AActor *owner, float attackRate)
    : UAttackComponent{owner},
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
    TWeakPtr<AProjectile> laserBeam = GetOwner()->GetCurrentWorld()->SpawnActor<ALaserBeam>(GetOwner());
    laserBeam.lock()->SetActorLocation(GetOwner()->GetActorLocation());
}

} // namespace Nonsense