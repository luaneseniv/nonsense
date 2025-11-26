#include <SFML/Graphics.hpp>
#include <string.h>

namespace Nonsense
{

class Application
{
public:
    Application();
    Application(const std::string& windowTitle, unsigned int windowWidth, unsigned int windowHeight);

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

} // namespace Nonsense
