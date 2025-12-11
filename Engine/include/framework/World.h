#pragma once
#include "framework/Core.h"

namespace Nonsense
{
class Application;
class AActor;

class UWorld
{
public:
    UWorld(Application* owningApp);
    virtual ~UWorld();

    void InternalBeginPlay();
    void InternalTick(float deltaTime);

    // Template function for creating new AActor from a specific actor type
    template <typename ActorType>
    TWeakPtr<ActorType> SpawnActor();

private:
    void Tick(float deltaTime);
    void BeginPlay();

    Application* mOwningApp;
    bool mBeganPlay;

    TArray<TSharedPtr<AActor>> mActors;
    TArray<TSharedPtr<AActor>> mPendingActors;

};

template <typename ActorType>
TWeakPtr<ActorType> UWorld::SpawnActor()
{
    TSharedPtr<ActorType> newActor { new ActorType{this} };
    mPendingActors.push_back(newActor);

    return newActor;
}

} // namespace Nonsense