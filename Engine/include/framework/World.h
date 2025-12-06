#pragma once


namespace Nonsense
{
class Application;

class World
{
public:
    World(Application* owningApp);
    virtual ~World();

    void InternalBeginPlay();
    void InternalTick(float deltaTime);

private:
    void Tick(float deltaTime);
    void BeginPlay();

    Application* mOwningApp;
    bool mBeganPlay;
};

} // namespace Nonsense