#pragma once

#include "framework/Object.h"


namespace Nonsense
{
    
class UWorld;

class AActor : public UObject
{

public:
    AActor(UWorld* owningWorld);
    virtual ~AActor();

    virtual void BeginPlay();
    virtual void Tick(float deltaTime);

private:
    UWorld* mOwningWorld;
};


} // namespace nonsense