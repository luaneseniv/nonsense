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

    // These functions are called from World class
    void InternalBeginPlay();
    void InternalTick(float deltaTime);
    
    // virtual functions
    // child classes can override and implement their own logics
    virtual void BeginPlay();
    virtual void Tick(float deltaTime);

    void SetTexture(const FString& texturePath);
    void Render(sf::RenderWindow& window); // this function is called from the world's Render()

    UWorld* GetCurrentWorld() const { return mOwningWorld; };

    // Actor's transform Get-Set
    sf::Vector2f GetActorLocation() const;
    float GetActorRotation() const;
    sf::Vector2f GetActorForwardVector() const;
    sf::Vector2f GetActorRightVector() const;
    void SetActorLocation(const sf::Vector2f& newLocation);
    void SetActorRotation(float newRotation);
    void AddActorLocationOffset(const sf::Vector2f& deltaLocation);
    void AddActorRotationOffset(float deltaRotation);

    sf::FloatRect GetActorBound() const;
    bool IsActorOutOfWindow() const;

private:
    UWorld* mOwningWorld;
    bool mHasBeganPlay;
    
    // from SFML 3 sf::Sprite doen't have default constructure
    // store the sprite as std::optional and init it from AActor::SetTexture()
    TSharedPtr<sf::Texture> mTexture;
    TOptional<sf::Sprite> mSprite;
    sf::Vector2f mPivot;
};


} // namespace nonsense