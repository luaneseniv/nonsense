#pragma once
#include <SFML/Graphics.hpp>

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
    void Render(sf::RenderWindow& window);
    void CleanCycle();

    // Template function for creating new AActor from a specific actor type
    template <typename ActorType, typename ...Args>
    TWeakPtr<ActorType> SpawnActor(Args...);

private:
    void Tick(float deltaTime);
    void BeginPlay();

private:
    Application* mOwningApp;
    bool mBeganPlay;

    TArray<TSharedPtr<AActor>> mActors;
    TArray<TSharedPtr<AActor>> mPendingActors;

public: // getters setters
    sf::Vector2u GetWindowSize() const;
};

template <typename ActorType, typename ...Args>
TWeakPtr<ActorType> UWorld::SpawnActor(Args... args)
{
    TSharedPtr<ActorType> newActor { new ActorType{this, args...} };
    mPendingActors.push_back(newActor);

    return newActor;
}

} // namespace Nonsense