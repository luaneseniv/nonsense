#pragma once
#include <framework/Application.h>

namespace Nonsense
{

class GameApplication : public Application
{
public:
    GameApplication();

    virtual void Tick(float deltaTime) override;
    

};

} // namespace Nonsense