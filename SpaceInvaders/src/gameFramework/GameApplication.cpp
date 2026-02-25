#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

#include "config.h"
//#include "framework/Core.h"


Nonsense::Application* GetApplication()
{
    return new Nonsense::GameApplication{};
}

namespace Nonsense
{

GameApplication::GameApplication()
    : Application{1280, 720, "Space Invaders", sf::Style::None} // frameless, no titlebar
{
    // TEST: Create new world.
    testWorld = LoadWorld<UWorld>();
    testActor = testWorld.lock()->SpawnActor<AActor>();
    testActor.lock()->SetTexture(GetResourceDirectory() + "SpaceShips/T_SpaceShip_v1.png");
    destroyTime = 2.0f;

}

void GameApplication::Tick(float deltaTime)
{
    accumulated += deltaTime;

    if(accumulated > destroyTime)
    {
        if(!testActor.expired())
        {
            testActor.lock()->Destroy();
        }
    }

}

} // namespace Nonsense