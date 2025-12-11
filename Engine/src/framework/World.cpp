#include "framework/World.h"
#include "framework/Actor.h"

namespace Nonsense
{

UWorld::UWorld(Application* owningApp)
    :   mOwningApp{owningApp},
        mBeganPlay{false},
        mActors{},
        mPendingActors{}
{}

UWorld::~UWorld()
{}

void UWorld::InternalBeginPlay()
{
    if (!mBeganPlay)
    {
        mBeganPlay = true;
        BeginPlay();
    }
}

void UWorld::InternalTick(float deltaTime)
{
    // Adds pending actors to the actor array
    // This should be happend before the world's Tick()
    for (TSharedPtr<AActor> actor : mPendingActors)
    {
        mActors.push_back(actor);
        // Actor BeginPlay
        actor->BeginPlay();
    }
    mPendingActors.clear();

    // Actors tick
    for (TSharedPtr<AActor> actor : mActors)
    {
        actor->Tick(deltaTime);
    }

    // World tick
    Tick(deltaTime);
}

void UWorld::BeginPlay()
{
    NS_LOG("World Begin Play!");
}

void UWorld::Tick(float deltaTime)
{

}


} // namespace Nonsense