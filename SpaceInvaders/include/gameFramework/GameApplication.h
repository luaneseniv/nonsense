#pragma once
#include <framework/Application.h>


namespace Nonsense
{

class GameApplication : public Application
{
public:
    GameApplication();
    ~GameApplication();

    virtual void Tick(float deltaTime) override;
    

private:
    // testing
    TWeakPtr<class UWorld> testWorld;
    TWeakPtr<class APlayerSpaceship> testActor;

};

} // namespace Nonsense