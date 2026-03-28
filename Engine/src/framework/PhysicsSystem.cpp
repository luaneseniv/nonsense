#include <box2d/box2d.h>
#include <SFML/System/Vector2.hpp>

#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

//test
#include "SFML/Graphics.hpp"


namespace Nonsense
{

PhysicsSystem& PhysicsSystem::Get()
{
    static PhysicsSystem instance;
    return instance;
}

void PhysicsSystem::Tick(float deltaTime)
{
    ProcessPendingRemoveListeners();
    b2World_Step(mPhysicsWorldId, deltaTime, mSubSteps);

    b2SensorEvents sensorEvents = b2World_GetSensorEvents(mPhysicsWorldId);

    OnBeginOverlapEvents(sensorEvents);
    OnEndOverlapEvents(sensorEvents);
}

b2BodyId PhysicsSystem::AddListener(AActor *listener, bool isBullet)
{
    if (!listener || listener->IsPendingDestroy()) return b2_nullBodyId;

    b2Vec2 listenerLocation = ToB2Vector2(listener->GetActorLocation());
    ScaleVector(listenerLocation, GetPhysicsScale());


    // inits the body definition for the listener
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = reinterpret_cast<void*>(listener);
    bodyDef.isBullet = isBullet;
    bodyDef.position = listenerLocation;
    bodyDef.rotation = b2MakeRot(Deg2Rad(listener->GetActorRotation()));
    // Creates body ID from the body
    b2BodyId bodyId = b2CreateBody(mPhysicsWorldId, &bodyDef);

    // Creates circle collider shape
    float radius = listener->GetActorRadius() * GetPhysicsScale();
    b2Circle circle;
    circle.center = b2Vec2_zero;
    circle.radius = radius;

    
    // Shape definitions
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    shapeDef.isSensor = true;
    shapeDef.enableSensorEvents = true;
    
    b2ShapeId shapeId = b2CreateCircleShape(bodyId, &shapeDef, &circle);

    return bodyId;
}

void PhysicsSystem::RemoveListener(b2BodyId& listenerBody)
{
    if (b2Body_IsValid(listenerBody))
    {
        mPendingRemoveListeners.push_back(listenerBody);
        listenerBody = b2_nullBodyId;
    }
}

void PhysicsSystem::OnBeginOverlapEvents(const b2SensorEvents& sensorEvents)
{
    if (sensorEvents.beginCount > 0)
    {
        for (int i = 0; i < sensorEvents.beginCount; ++i)
        {
            const b2SensorBeginTouchEvent& event = sensorEvents.beginEvents[i];

            AActor* actor1 = reinterpret_cast<AActor*>(b2Body_GetUserData(b2Shape_GetBody(event.sensorShapeId)));
            AActor* actor2 = reinterpret_cast<AActor*>(b2Body_GetUserData(b2Shape_GetBody(event.visitorShapeId)));
            
            if (actor1 && !actor1->IsPendingDestroy())
            {
                actor1->OnActorBeginOverlap(actor2);
            }

            if (actor2 && !actor2->IsPendingDestroy())
            {
                actor2->OnActorBeginOverlap(actor1);
            }
        }
    }
}
void PhysicsSystem::OnEndOverlapEvents(const b2SensorEvents& sensorEvents)
{
    if(sensorEvents.endCount > 0)
    {
        for (int i = 0; i < sensorEvents.endCount; ++i)
        {
            const b2SensorEndTouchEvent& event = sensorEvents.endEvents[i];

            if (b2Shape_IsValid(event.sensorShapeId) && b2Shape_IsValid(event.visitorShapeId))
            {
                AActor* actor1 = reinterpret_cast<AActor*>(b2Body_GetUserData(b2Shape_GetBody(event.sensorShapeId)));
                AActor* actor2 = reinterpret_cast<AActor*>(b2Body_GetUserData(b2Shape_GetBody(event.visitorShapeId)));
    
                if (actor1 && !actor1->IsPendingDestroy())
                {
                    actor1->OnActorEndOverlap(actor2);
                }
                
                if (actor2 && !actor2->IsPendingDestroy())
                {
                    actor2->OnActorEndOverlap(actor1);
                }
            }
        }
    }
}

PhysicsSystem::PhysicsSystem()
    : mPhysicsWorldId{b2_nullWorldId},
      mPhysicsScale{0.01f}, // converts m to cm
      mSubSteps{4},         // initial sub-step = 4 regarding the documentation
      mPendingRemoveListeners{},
      mDebugDraw{}
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
    worldDef.gravity = b2Vec2_zero;
    mPhysicsWorldId = b2CreateWorld(&worldDef);

}

void PhysicsSystem::ProcessPendingRemoveListeners()
{
    if (mPendingRemoveListeners.size() == 0)
        return;

    for (auto& body : mPendingRemoveListeners)
    {
        b2DestroyBody(body);
    }

    mPendingRemoveListeners.clear();
}

#pragma region Debug
void PhysicsSystem::InitDebugDrawer(sf::RenderWindow &window)
{
    mDebugDraw = b2DefaultDebugDraw();
    mDebugDraw.drawShapes = true;

    mDebugDraw.DrawCircleFcn = DrawDebugCircle;
    mDebugDraw.context = &window;
}

void PhysicsSystem::DrawDebugCircle(b2Vec2 center, float radius, b2HexColor color, void* context) 
{
    const auto window = static_cast<sf::RenderWindow*>(context);

    sf::Vector2f location{ (center.x - radius) * 100.0f, (center.y - radius)  * 100.0f};

    sf::CircleShape circle(radius * 100.0f);
    circle.setFillColor(sf::Color::Transparent);
    // circle.setOutlineColor(sf::Color{(color & 0xFFFFFF00) | 0x66});
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(1.0f);
    circle.setPosition(location);

    window->draw(circle);
}

void PhysicsSystem::DrawDebug()
{
    b2World_Draw(mPhysicsWorldId, &mDebugDraw);
}
#pragma endregion

} // namespace Nonsense