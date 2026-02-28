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
    testActor = testWorld.lock()->SpawnActor<APlayerSpaceship>();
    // testActor.lock()->SetTexture("SpaceShips/T_SpaceShip_v1.png");
    testActor.lock()->SetActorLocation(sf::Vector2f{640.0f, 360.0f});
    // dynamic_cast<ASpaceship*>(testActor.lock().get())->SetVelocity(sf::Vector2f{0.0f, -100.0f});
    testActor.lock()->SetSpeed(200.0f);


}

GameApplication::~GameApplication()
{

}

void GameApplication::Tick(float deltaTime)
{
    Application::Tick(deltaTime);
}

} // namespace Nonsense