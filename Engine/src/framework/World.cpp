#include "framework/World.h"
#include "framework/Application.h"
#include "framework/Core.h"


namespace Nonsense
{

World::World(Application* owningApp)
    : mOwningApp{owningApp},
    mBeganPlay{false}
{}

World::~World()
{}

void World::InternalBeginPlay()
{
    if (!mBeganPlay)
    {
        mBeganPlay = true;
        BeginPlay();
    }
}

void World::InternalTick(float deltaTime)
{
    Tick(deltaTime);
}

void World::BeginPlay()
{
    NS_LOG("World Begin Play!");
}

void World::Tick(float deltaTime)
{

}


} // namespace Nonsense