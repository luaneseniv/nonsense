#pragma once
#include <box2d/id.h>
#include <box2d/types.h>

#include "framework/Core.h"

//TEST
#include <SFML/Graphics/RenderWindow.hpp>

struct b2SensorEvents;

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
    void RemoveListener(b2BodyId& listenerBody);

    void OnBeginOverlapEvents(const b2SensorEvents& sensorEvents);
    void OnEndOverlapEvents(const b2SensorEvents& sensorEvents);

public:   // Temporary functions for debugging
    void InitDebugDrawer(sf::RenderWindow& window);
    static void DrawDebugCircle(b2Vec2 center, float radius, b2HexColor color, void* context);
    void DrawDebug();


private:
    PhysicsSystem();
    ~PhysicsSystem();

    void CreateWorld();
    void ProcessPendingRemoveListeners();

private:
    TArray<b2BodyId> mPendingRemoveListeners;
    b2WorldId mPhysicsWorldId;
    float mPhysicsScale;
    int mSubSteps;
    

private: // Temporary for Debugging
    b2DebugDraw mDebugDraw;

public: // Getters
    float GetPhysicsScale() const { return mPhysicsScale; }
    b2WorldId GetPhysicsWorld() const { return mPhysicsWorldId; }

};

} // namespace Nonsense