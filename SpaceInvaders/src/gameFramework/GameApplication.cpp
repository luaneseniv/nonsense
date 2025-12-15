#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

#include "framework/Core.h"


Nonsense::Application* GetApplication()
{
    return new Nonsense::GameApplication{};
}

namespace Nonsense
{

GameApplication::GameApplication()
    : Application{1280, 720, "Space Invaders", sf::Style::None} // frameless, no titlebar
{
    NS_LOG("Created new game session!");

    // TEST: Create new world.
    TWeakPtr<UWorld> testWorld = LoadWorld<UWorld>();
    testWorld.lock()->SpawnActor<AActor>();
    testWorld.lock()->SpawnActor<AActor>().lock()->Destroy();

}

void GameApplication::Tick(float deltaTime)
{

}

} // namespace Nonsense