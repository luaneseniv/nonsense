#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"


namespace Nonsense
{
    
class UWorld;

class AActor : public UObject
{
public:
    AActor(UWorld* owningWorld, const FString& texturePath = "");
    virtual ~AActor();
    void InternalBeginPlay();
    void InternalTick(float deltaTime);
    virtual void BeginPlay();
    virtual void Tick(float deltaTime);

    void SetTexture(const FString& texturePath);
    void Render(sf::RenderWindow& window);

private:
    UWorld* mOwningWorld;
    bool mHasBeganPlay;

    // uses std::optional because the sf::Sprite requires a texture in the constructor
    TOptional<sf::Sprite> mSprite;
    TSharedPtr<sf::Texture> mTexture;
};


} // namespace nonsense