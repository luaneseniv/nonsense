#include "framework/Object.h"

#include "framework/Core.h"

namespace Nonsense
{

UObject::UObject()
    : mIsPedingDestroy{false}
{

}

UObject::~UObject()
{
    NS_LOG("Object has been destroyed!");
}

void UObject::Destroy()
{
    mIsPedingDestroy = true;
}


} // namespace Nonsense