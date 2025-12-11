#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace Nonsense
{
class UWorld;

class Application
{
public:
    Application();

    void SetWindowConfigs(FString title, unsigned int windowWidth, unsigned int windowHeight);
    
    // Moves the window's position to the center of the screen.
    // By default, the init position (Top-Left corner) of the SF window always stay at the center of the screen.
    // Maybe SF has ability to do this, but for now let's set it from the Application.
    void UpdateWindowPosition();

    void Run();

    // Template function for creating new world from a specific world type.
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

    TSharedPtr<UWorld> mCurrentWorld;
};


template <typename WorldType>
TWeakPtr<WorldType> Application::LoadWorld()
{
    TSharedPtr<WorldType> newWorld{ new WorldType{this} };
    mCurrentWorld = newWorld;
    return newWorld;
}

} // namespace Nonsense
