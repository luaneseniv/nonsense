#include "framework/Actor.h"

#include "framework/Core.h"

namespace Nonsense
{

AActor::AActor(UWorld* owningWorld)
    : mOwningWorld{owningWorld}
{

}

AActor::~AActor()
{
    NS_LOG("Actor destroyed!");
}

void AActor::BeginPlay()
{
    NS_LOG("Actor Begin Play");
}

void AActor::Tick(float deltaTime)
{

}



} // namespace Nonsene