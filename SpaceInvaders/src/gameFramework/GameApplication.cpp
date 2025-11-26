#include "gameFramework/GameApplication.h"


Nonsense::Application* GetApplication()
{
    return new Nonsense::GameApplication{"Space Invaders", 600, 900};
}

namespace Nonsense
{


} // namwspace Nonsense