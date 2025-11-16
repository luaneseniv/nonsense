#include <SFML/Graphics.hpp>

namespace Nonsense
{
    class Application
    {
    public:
        Application();
        void Run();

    private:

        void RenderInternal();
        void TickInternal(float deltaTime);

        void Render();
        void Tick(float deltaTime);

        sf::RenderWindow mWindow;

        float mTargetFrameRate;
        sf::Clock mTickClock;
    };
}
