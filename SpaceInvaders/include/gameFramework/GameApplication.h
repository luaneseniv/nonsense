#pragma once
#include <SFML/Graphics.hpp>

#include <framework/Application.h>


namespace Nonsense
{

class GameApplication : public Application
{
public:
    GameApplication();

    virtual void Tick(float deltaTime) override;
    
    float accumulated = 0.0f;
    float destroyTime = 0.0f;

private:
    // testing
    TWeakPtr<UWorld> testWorld;
    TWeakPtr<class AActor> testActor;

};

} // namespace Nonsense