#include "framework/Application.h"


namespace Nonsense
{

Application::Application()
    : mWindow{sf::VideoMode({600, 900}), "Game Window"},
    mTargetFrameRate{60.0f}
{}

Application::Application(const std::string& windowTitle, unsigned int windowWidth, unsigned int windowHeight)
    : mWindow{sf::VideoMode({windowWidth, windowHeight}), windowTitle},
    mTargetFrameRate{60.0f}
{}

void Application::Run()
{
    mTickClock.restart();
    float targetDeltaTime = 1.0f / mTargetFrameRate;
    float accumulatedTime = 0.0f;

    while(mWindow.isOpen())
    {
        while(const std::optional<sf::Event> event = mWindow.pollEvent())
        {
            if(event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() &&
                    event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
                mWindow.close();
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
}

void Application::Render()
{
}

void Application::Tick(float deltaTime)
{
}

} // namespace Nonsense
