#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace Nonsense
{
class World;

class Application
{
public:
    Application();

    void SetWindowConfigs(FString title, unsigned int windowWidth, unsigned int windowHeight);

    void Run();

    template <typename WorldType>
    TWeakPtr<WorldType> LoadWorld();

private:

    void RenderInternal();
    void TickInternal(float deltaTime);

    void Render();
    void Tick(float deltaTime);

    sf::RenderWindow mWindow;

    float mTargetFrameRate;
    sf::Clock mTickClock;

    TSharedPtr<World> mCurrentWorld;
};

template <typename WorldType>
TWeakPtr<WorldType> Application::LoadWorld()
{
    TSharedPtr<WorldType> newWorld{ new WorldType(this) };
    mCurrentWorld = newWorld;
    return newWorld;
}

}; // namespace Nonsense
