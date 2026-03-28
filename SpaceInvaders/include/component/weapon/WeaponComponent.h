#pragma once


namespace Nonsense
{
class AActor;

class UWeaponComponent
{
public:
    void Attack();
    virtual bool CanAttack() const { return true; }
    virtual bool IsOnCooldown() const { return false; }


protected:
    UWeaponComponent(AActor* owner);

private:
    virtual void AttackImpl() = 0;

private:
    AActor* mOwner;

public:
    AActor* GetOwner() const { return mOwner; }
};

} // namespace Nonsense