#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace Nonsense
{
class UWorld;

class Application
{
public:
    Application(unsigned int windowWidth, unsigned int windowHeight,const FString& title, std::uint32_t style);

    ~Application();

    void SetTargetFramerate(float newFramerate);
    void Run();

    virtual void Tick(float deltaTime);

    // Template function for creating new world from a specific world type.
    template <typename WorldType>
    TWeakPtr<WorldType> LoadWorld();

    // Return loading world
    TSharedPtr<UWorld> GetCurrentWorld() const { return mCurrentWorld; };

private:
    void InternalRender();
    void InternalTick(float deltaTime);
    virtual void Render();

    sf::RenderWindow mWindow;

    float mTargetFrameRate;
    sf::Clock mTickClock;

    // Asset cleaning cycle
    float mCleanCycleIterval;
    sf::Clock mCleanCycleClock;

    TSharedPtr<UWorld> mCurrentWorld;

    ///////////// TEST /////////////
    float accumulator = 0.0f;
    float mFPS = 0.0f;
    int mFrameCount = 0;
    sf::Clock testClock;
    sf::Text mFpsText;
    const sf::Font mFont{"JetBrainsMono-Medium.ttf"};
    // end TEST
};


template <typename WorldType>
TWeakPtr<WorldType> Application::LoadWorld()
{
    TSharedPtr<WorldType> newWorld{ new WorldType{this} };
    mCurrentWorld = newWorld;
    return newWorld;
}

} // namespace Nonsense
