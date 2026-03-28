#include "gameFramework/GameApplication.h"
#include "framework/AssetManager.h"
#include "framework/World.h"
#include "player/playerSpaceship.h"

#include "config.h"
//#include "framework/Core.h"


Nonsense::Application* GetApplication()
{
    return new Nonsense::GameApplication{};
}

namespace Nonsense
{

GameApplication::GameApplication()
    : Application{1280, 720, "Space Invaders", sf::Style::Titlebar | sf::Style::Close} // sf::Style::None : frameless, no titlebar
{
    SetTargetFramerate(60.0f);
    AssetManager::Get().SetContentDirectory(GetContentDirectory());
    // TEST: Create new world.
    testWorld = LoadWorld<UWorld>();

    // Test Player
    testActor = testWorld.lock()->SpawnActor<APlayerSpaceship>();
    testActor.lock()->SetActorLocation(sf::Vector2f{640.0f, 360.0f});
    // dynamic_cast<ASpaceship*>(testActor.lock().get())->SetVelocity(sf::Vector2f{0.0f, -100.0f});
    testActor.lock()->SetSpeed(300.0f);

    TWeakPtr<ASpaceship> newActor = testWorld.lock()->SpawnActor<ASpaceship>();
    newActor.lock()->SetActorLocation({640.0f, 150.0f});
    newActor.lock()->SetTexture("SpaceShips/T_Ship_X.png");


}

GameApplication::~GameApplication()
{

}

void GameApplication::Tick(float deltaTime)
{

}

} // namespace Nonsense