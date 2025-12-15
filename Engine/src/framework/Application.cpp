#include "framework/Application.h"
#include "framework/World.h"


namespace Nonsense
{

Application::Application(unsigned int windowWidth, unsigned int windowHeight,const FString& title, std::uint32_t style)
    :   mWindow{sf::VideoMode({windowWidth, windowHeight}), title, style},
        mTargetFrameRate{60.0f},
        mCurrentWorld{nullptr}
{

}

// Set game window at the center of the screen
void Application::UpdateWindowPosition()
{
    mWindow.setPosition((sf::Vector2<int>(mWindow.getSize()) - mWindow.getPosition()) / 2);
}

void Application::Run()
{
    UpdateWindowPosition();
    
    mTickClock.restart();
    float targetDeltaTime = 1.0f / mTargetFrameRate;
    float accumulatedTime = 0.0f;
    
    NS_LOG("Starting the game...");
    while(mWindow.isOpen())
    {
        // Poll Events
        while(const std::optional<sf::Event> event = mWindow.pollEvent())
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
            TickInternal(targetDeltaTime);
            RenderInternal();
        }
    }
}


void Application::RenderInternal()
{
    mWindow.clear();

    Render();

    mWindow.display();
}

void Application::TickInternal(float deltaTime)
{
    Tick(deltaTime);

    if (mCurrentWorld)
    {
        mCurrentWorld->InternalBeginPlay();
        mCurrentWorld->InternalTick(deltaTime);
    }
}

void Application::Render()
{
}

void Application::Tick(float deltaTime)
{
}

} // namespace Nonsense
