#pragma once
#include "string"

std::string GetResourceDirectory()
{
#ifdef SHIPPING_BUILD
    return "content/";
#else
    return "D:/nonsense/SpaceInvaders/content/";
#endif
}
