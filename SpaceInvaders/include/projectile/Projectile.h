#pragma once
#include "framework/Actor.h"

namespace Nonsense
{

class UWorld;

class AProjectile : public AActor
{
public:
    AProjectile(UWorld* owingWorld, AActor* owner, const FString& texturePath = "", float speed, float damage);
    virtual void Tick(float deltaTime) override;
    void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
    float GetSpeed() const { return mSpeed; }
    void SetDamage(float newDamage) { mDamage = newDamage; }
    float GetDamage() const { return mDamage; }
    
private:
    virtual void Move(float deltaTime);
    AActor* mOwner;
    float mSpeed;
    float mDamage;

};


} // namespace Nonsense