#pragma once
#include "string"

std::string GetContentDirectory()
{
#ifdef SHIPPING_BUILD
    return "content/";
#else
    return "L:/_Projects/_Eseniv/nonsense/SpaceInvaders/content/";
#endif
}
