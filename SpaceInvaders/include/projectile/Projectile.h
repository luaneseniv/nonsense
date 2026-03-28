#pragma once
#include "framework/Actor.h"

namespace Nonsense
{

class UWorld;

class AProjectile : public AActor
{
public:
    AProjectile(UWorld* owingWorld, AActor* owner, const FString& texturePath = "", float speed = 100.0f, float damage = 1.0f);

    virtual void Tick(float deltaTime) override;

protected:
    virtual void BeginPlay() override;

private: // functions
    virtual void Move(float deltaTime);
    
private: // variables
    AActor* mOwner;
    float mSpeed;
    float mDamage;

public: // Getters Setters
    float GetSpeed() const { return mSpeed; }
    float GetDamage() const { return mDamage; }

    void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
    void SetDamage(float newDamage) { mDamage = newDamage; }
};


} // namespace Nonsense