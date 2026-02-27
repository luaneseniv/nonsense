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

    // Actor's transform SET
    void SetActorLocation(const sf::Vector2f& newLocation);
    void SetActorRotation(float newRotation);
    void AddActorLocationOffset(const sf::Vector2f& deltaLocation);
    void AddActorRotationOffset(float deltaRotation);
    // Actor's transform GET
    sf::Vector2f GetActorLocation() const;
    float GetActorRotation() const;
    sf::Vector2f GetActorForwardVector() const;
    sf::Vector2f GetActorRightVector() const;

private:
    UWorld* mOwningWorld;
    bool mHasBeganPlay;
    
    // uses std::optional because the sf::Sprite requires a texture in the constructor
    TOptional<sf::Sprite> mSprite;
    TSharedPtr<sf::Texture> mTexture;
    sf::Vector2f mPivot;
};


} // namespace nonsense