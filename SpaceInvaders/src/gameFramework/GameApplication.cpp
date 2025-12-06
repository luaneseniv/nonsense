#include "gameFramework/GameApplication.h"
#include "framework/Core.h"
#include "framework/World.h"


Nonsense::Application* GetApplication()
{
    return new Nonsense::GameApplication{};
}

namespace Nonsense
{
    GameApplication::GameApplication()
    {
        NS_LOG("Created new game session!");
        SetWindowConfigs("Space Invader", 600, 900);

        // TEST: Create new world.
        LoadWorld<World>();
    }

} // namwspace Nonsense