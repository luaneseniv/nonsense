#include "framework/Application.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"

namespace Nonsense
{

Application::Application(unsigned int windowWidth, unsigned int windowHeight,const FString& title, std::uint32_t style)
    :   mWindow{sf::VideoMode({windowWidth, windowHeight}), title, style},
        mTargetFrameRate{60.0f},
        mTickClock{},
        mCurrentWorld{nullptr},
        mCleanCycleIterval{5.0f},
        mCleanCycleClock{},
        // test
        mFpsText{mFont},
        testClock{}
{
    // init the logger
#ifdef LOG_FILE_PATH
    Logger::Get().Init(LOG_FILE_PATH);
#else
    Logger::Get().Init("temp.log");
#endif

}

Application::~Application()
{

}

void Application::SetTargetFramerate(float newFramerate)
{
    if(newFramerate > 0.0f)
    {
        mTargetFrameRate = newFramerate;
        mWindow.setFramerateLimit(newFramerate);
    }
    NS_LOG("Max FPS was set to %f.", mTargetFrameRate);
}

void Application::Run()
{
    // Debug: initialize the shape drawer
    PhysicsSystem::Get().InitDebugDrawer(mWindow);
    // end Debug

    mTickClock.restart();
    float targetDeltaTime = 1.0f / mTargetFrameRate;
    float accumulatedTime = 0.0f;
    
    //////////// TEST /////////////
    mFpsText.setCharacterSize(20);
    mFpsText.setFillColor(sf::Color::White);
    mFpsText.setPosition({10.f, 10.f});
    mFrameCount = 0;
    testClock.reset();
    //////////////////////////////

#ifdef SHIPPING_BUILD
    NS_LOG("Starting the game... Shipping build.");
#else
    NS_LOG("Starting the game... Development build.");
#endif

    // game loop
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
                NS_LOG("Game Window has been Closed.");
            }
        }

        // fixed framerate updating
        accumulatedTime += mTickClock.restart().asSeconds();
        while (accumulatedTime >= targetDeltaTime)
        {
            accumulatedTime -= targetDeltaTime;
            InternalTick(targetDeltaTime);
        }
        
        InternalRender();
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

    // World Tick
    if (mCurrentWorld)
    {
        mCurrentWorld->InternalBeginPlay();
        mCurrentWorld->InternalTick(deltaTime);
    }

    // Physics tick
    PhysicsSystem::Get().Tick(deltaTime);

    // cleanup unused textures
    // runs every 10 seconds
    if(mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleIterval)
    {
        mCleanCycleClock.restart();
        AssetManager::Get().CleanCycle(); // Textures cleaning

        if (mCurrentWorld)
        {
            mCurrentWorld->CleanCycle(); // Actors cleaning
        }
    }

}

void Application::Render()
{
    //////// TEST ///////////
    mFrameCount++;

    accumulator += testClock.restart().asSeconds();
    // Update the FPS display every second
    if (accumulator >= 1.0f)
    {
        //NS_LOG("Frame Count %d", mFrameCount);
        mFPS = mFrameCount / accumulator;

        // Format the FPS value for display
        std::stringstream ss;
        ss << std::fixed << std::setprecision(4) << mFPS << " FPS";
        mFpsText.setString(ss.str());
        mFrameCount = 0;
        accumulator = 0.0f;
    }
    
    mWindow.draw(mFpsText);
    //////// End TEST ////////////////

    if(mCurrentWorld)
    {
        mCurrentWorld->Render(mWindow);
    }

    // Debug: Draw debug shapes
    PhysicsSystem::Get().DrawDebug();
    // end debug


}

void Application::Tick(float deltaTime)
{

}

sf::Vector2u Application::GetWindowSize() const
{
    return mWindow.getSize();
}
} // namespace Nonsense
