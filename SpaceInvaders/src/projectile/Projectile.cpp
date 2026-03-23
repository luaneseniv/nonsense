#include "projectile/Projectile.h"


namespace Nonsense
{

AProjectile::AProjectile(UWorld* owingWorld, AActor* owner, const FString& texturePath, float speed, float damage)
    : AActor{owingWorld, texturePath},
    mOwner{owner},
    mSpeed{speed},
    mDamage{damage}
{

}

void AProjectile::Tick(float deltaTime)
{
    AActor::Tick(deltaTime);

    Move(deltaTime);

}

void AProjectile::BeginPlay()
{
    AActor::BeginPlay();
    SetEnablePhysics(true, true);
}

void AProjectile::Move(float deltaTime)
{
    AddActorLocationOffset(GetActorForwardVector() * mSpeed * deltaTime);
}

} // namespace Nonsense