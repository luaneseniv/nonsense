#include "projectile/LaserBeam.h"


namespace Nonsense
{

ALaserBeam::ALaserBeam(UWorld *owningWorld, AActor *owner, const FString &texturePath, float speed, float damage)
    : AProjectile{owningWorld, owner, texturePath, speed, damage}
{

}


}// namespace Nonsense
