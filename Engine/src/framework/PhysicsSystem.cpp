#include <box2d/box2d.h>
#include <SFML/System/Vector2.hpp>

#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"


namespace Nonsense
{

PhysicsSystem& PhysicsSystem::Get()
{
    static PhysicsSystem instance;
    return instance;
}

void PhysicsSystem::Tick(float deltaTime)
{
    b2World_Step(mPhysicsWorldId, deltaTime, mSubSteps);
}

b2BodyId PhysicsSystem::AddListener(AActor *listener, bool isBullet)
{
    if (!listener || listener->IsPendingDestroy()) return b2_nullBodyId;

    // convert Location of the listener to b2Vec2
    b2Vec2 listenerLocation = ToB2Vector2(listener->GetActorLocation());

    
    // inits the body definition for the listener
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = reinterpret_cast<void*>(listener);
    bodyDef.isBullet = isBullet;
    bodyDef.position = ScaleVector<b2Vec2>(listenerLocation, GetPhysicsScale()); // Scales to cm
    bodyDef.rotation = b2MakeRot(Deg2Rad(listener->GetActorRotation()));
    // Creates body ID from the body
    b2BodyId bodyId = b2CreateBody(mPhysicsWorldId, &bodyDef);


    // Creates circle collider shape
    float radius = listener->GetActorBound().size.x * GetPhysicsScale();
    b2Vec2 center = ToB2Vector2(listener->GetActorPivot());
    ScaleVector(center, GetPhysicsScale());
    
    b2Circle circle;
    circle.center = center;
    circle.radius = radius;


    // Shape definitions
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    shapeDef.isSensor = true;

    b2CreateCircleShape(bodyId, &shapeDef, &circle);

    return bodyId;
}

PhysicsSystem::PhysicsSystem()
    : mPhysicsWorldId{b2_nullWorldId},
      mPhysicsScale{0.01f}, // converts m to cm
      mSubSteps{4} // initial sub-step = 4 regarding the documentation
{
    CreateWorld();
}

PhysicsSystem::~PhysicsSystem()
{
    // destroy the world and everything inside the world.
    b2DestroyWorld(mPhysicsWorldId);
    mPhysicsWorldId = b2_nullWorldId;
}

void PhysicsSystem::CreateWorld()
{
    // check if there's an exised world
    if (B2_IS_NON_NULL(mPhysicsWorldId))
    {
        b2DestroyWorld(mPhysicsWorldId);
        mPhysicsWorldId= b2_nullWorldId;
    }

    // create new world
    b2WorldDef worldDef = b2DefaultWorldDef();

    mPhysicsWorldId = b2CreateWorld(&worldDef);
}

} // namespace Nonsense