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
    // adds pending actors to the actor array.
    // this should be happend before the world's Tick()
    // this is a simple solution, not a good practice for memory management.
    // TODO: create an actor pool ~50 actors or ajustable pool size
    for (TSharedPtr<AActor> actor : mPendingActors)
    {
        mActors.push_back(actor);
        // Actor BeginPlay
        actor->InternalBeginPlay();
    }
    mPendingActors.clear();

    // Actors tick
    for (TArray<TSharedPtr<AActor>>::iterator it = mActors.begin(); it != mActors.end();)
    {
        if(it->get()->IsPendingDestroy())
        {
            it = mActors.erase(it);
        }
        else
        {
            it->get()->InternalTick(deltaTime);
            ++it;
        }
    }

    // World tick
    Tick(deltaTime);
}

void UWorld::BeginPlay()
{
    NS_LOG("World Begin Play!");
}

void UWorld::Render(sf::RenderWindow& window)
{
    for (auto& actor : mActors)
    {
        actor->Render(window);
    }
}

void UWorld::Tick(float deltaTime)
{

}


} // namespace Nonsense