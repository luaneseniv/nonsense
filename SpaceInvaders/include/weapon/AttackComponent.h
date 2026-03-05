#pragma once


namespace Nonsense
{
class AActor;

class UAttackComponent
{
public:

    void Attack();
    virtual bool CanAttack() const { return true; }
    virtual bool IsOnCooldown() const { return false; }
    AActor* GetOwner() const { return mOwner; }

protected:
    UAttackComponent(AActor* owner);

private:
    virtual void AttackImpl() = 0;
    AActor* mOwner;
};

} // namespace Nonsense