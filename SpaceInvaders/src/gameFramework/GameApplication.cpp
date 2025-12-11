#include "gameFramework/GameApplication.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/Actor.h"


Nonsense::Application* GetApplication()
{
    return new Nonsense::GameApplication{};
}

namespace Nonsense
{

GameApplication::GameApplication()
{
    NS_LOG("Created new game session!");
    SetWindowConfigs("Space Invader", 1280, 720);

    // TEST: Create new world.
    TWeakPtr<UWorld> testWorld = LoadWorld<UWorld>();
    testWorld.lock()->SpawnActor<AActor>();
    testWorld.lock()->SpawnActor<AActor>();
    testWorld.lock()->SpawnActor<AActor>();
}

} // namwspace Nonsense