#pragma once
#include <box2d/id.h>
#include "framework/Core.h"

namespace Nonsense
{
class AActor;

class PhysicsSystem
{
public:
    static PhysicsSystem& Get();
    PhysicsSystem (const PhysicsSystem&) = delete;
    PhysicsSystem& operator=(const PhysicsSystem&&) = delete;
    PhysicsSystem(PhysicsSystem&&) = delete;
    PhysicsSystem& operator=(PhysicsSystem&&) = delete;
    
    void Tick(float deltaTime);
    b2BodyId AddListener(AActor* listener, bool isBullet);

    float GetPhysicsScale() { return mPhysicsScale; }


private:
    PhysicsSystem();
    ~PhysicsSystem();
    void CreateWorld();

    b2WorldId mPhysicsWorldId;
    float mPhysicsScale;
    int mSubSteps;

};

} // namespace Nonsense