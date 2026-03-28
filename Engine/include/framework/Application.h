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
    void Run();

    // Template function for creating new world from a specific world type.
    template <typename WorldType>
    TWeakPtr<WorldType> LoadWorld();
    
    
private:
    void InternalRender();
    void InternalTick(float deltaTime);
    virtual void Tick(float deltaTime);
    virtual void Render();

private:
    sf::RenderWindow mWindow;

    float mTargetFrameRate;
    sf::Clock mTickClock;

    // Asset cleaning cycle
    float mCleanCycleIterval;
    sf::Clock mCleanCycleClock;

    TSharedPtr<UWorld> mCurrentWorld;

#pragma region test
private:
    float accumulator = 0.0f;
    float mFPS = 0.0f;
    int mFrameCount = 0;
    sf::Clock testClock;
    sf::Text mFpsText;
    const sf::Font mFont{"SpaceInvaders/content/fonts/JetBrainsMono-Medium.ttf"};
#pragma endregion

public: // getters setters
    sf::Vector2u GetWindowSize() const;
    TSharedPtr<UWorld> GetCurrentWorld() const { return mCurrentWorld; };

    void SetTargetFramerate(float newFramerate);

};


template <typename WorldType>
TWeakPtr<WorldType> Application::LoadWorld()
{
    TSharedPtr<WorldType> newWorld{ new WorldType{this} };
    mCurrentWorld = newWorld;
    return newWorld;
}

} // namespace Nonsense
