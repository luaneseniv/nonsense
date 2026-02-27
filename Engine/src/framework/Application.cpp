#include "framework/Application.h"
#include "framework/World.h"
#include "framework/AssetManager.h"

namespace Nonsense
{

Application::Application(unsigned int windowWidth, unsigned int windowHeight,const FString& title, std::uint32_t style)
    :   mWindow{sf::VideoMode({windowWidth, windowHeight}), title, style},
        mTargetFrameRate{60.0f},
        mTickClock{},
        mCurrentWorld{nullptr},
        mCleanCycleIterval{10.0f},
        mCleanCycleClock{}
{

}

Application::~Application()
{

}

void Application::SetTargetFramerate(float targetFramerate)
{
    mTargetFrameRate = targetFramerate;
    NS_LOG("Max FPS was set to %f.", targetFramerate);
}

void Application::Run()
{
    // UpdateWindowPosition();
    
    mTickClock.restart();
    float targetDeltaTime = 1.0f / mTargetFrameRate;
    float accumulatedTime = 0.0f;
    
#ifdef SHIPPING_BUILD
    NS_LOG("Starting the game... Shipping build.");
#else
    NS_LOG("Starting the game... Development build.");
#endif

    while(mWindow.isOpen())
    {
        // Poll Events
        while(const TOptional<sf::Event> event = mWindow.pollEvent())
        {
            // Close the window if user presses ESC or Window Close button
            if(event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() &&
                    event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
                {
                    mWindow.close();
                    NS_LOG("Game Window Closed.");
                }
        }

        // fixed framerate updating
        accumulatedTime += mTickClock.restart().asSeconds();
        while (accumulatedTime > targetDeltaTime)
        {
            accumulatedTime -= targetDeltaTime;
            InternalTick(targetDeltaTime);
            InternalRender();
        }
    }
}


void Application::InternalRender()
{
    mWindow.clear();

    Render();

    mWindow.display();
}

void Application::InternalTick(float deltaTime)
{
    Tick(deltaTime);

    if (mCurrentWorld)
    {
        mCurrentWorld->InternalBeginPlay();
        mCurrentWorld->InternalTick(deltaTime);
    }

    // cleanup unused textures
    // runs every 10 seconds
    if(mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleIterval)
    {
        mCleanCycleClock.restart();
        AssetManager::Get().CleanCycle();
    }

}

void Application::Render()
{
    if(mCurrentWorld)
    {
        mCurrentWorld->Render(mWindow);
    }

}

void Application::Tick(float deltaTime)
{
    NS_LOG("App Parent ticking");
}

} // namespace Nonsense
