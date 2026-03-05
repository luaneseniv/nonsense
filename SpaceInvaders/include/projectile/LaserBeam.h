#pragma once
#include "projectile/Projectile.h"

namespace Nonsense
{

class ALaserBeam : public AProjectile
{
public:
    ALaserBeam(UWorld* owningWorld, AActor* owner, const FString& texturePath = "SpaceShips/T_Projectile_Laser.png", float speed = 1200.0f, float damage = 10.0f);


};

} // namespace Nonsense