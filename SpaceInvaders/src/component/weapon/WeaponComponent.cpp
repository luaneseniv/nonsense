#include "component/weapon/WeaponComponent.h"


namespace Nonsense
{

void UWeaponComponent::Attack()
{
    if (CanAttack() && !IsOnCooldown())
    {
        AttackImpl();
    }
}

UWeaponComponent::UWeaponComponent(AActor *owner)
    : mOwner{owner}
{

}

} // namespace Nonsense
