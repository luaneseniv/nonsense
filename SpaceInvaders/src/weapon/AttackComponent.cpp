#include "weapon/AttackComponent.h"


namespace Nonsense
{

void UAttackComponent::Attack()
{
    if (CanAttack() && !IsOnCooldown())
    {
        AttackImpl();
    }
}

UAttackComponent::UAttackComponent(AActor *owner)
    : mOwner{owner}
{

}

} // namespace Nonsense
