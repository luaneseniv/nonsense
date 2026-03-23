#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/id.h>

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
    float GetActorRotation() const; // return rotation in degrees
    sf::Vector2f GetActorForwardVector() const;
    sf::Vector2f GetActorRightVector() const;
    void SetActorLocation(const sf::Vector2f& newLocation);
    void SetActorRotation(float newRotation);
    void AddActorLocationOffset(const sf::Vector2f& deltaLocation);
    void AddActorRotationOffset(float deltaRotation);

    sf::FloatRect GetActorBound() const;
    sf::Vector2f GetActorPivot() const;
    float GetActorRadius() const { return GetActorBound().size.x * 0.25f; }
    bool IsActorOutOfWindow() const;

    void SetEnablePhysics(bool enable, bool isBullet = false);

    virtual void OnActorBeginOverlap(AActor* other);
    virtual void OnActorEndOverlap(AActor* other);

private:
    void UpdateActorBound();
    void InitializePhysics(bool isBullet);
    void DeinitializePhysics();
    void UpdatePhysicsBodyTransform();

    UWorld* mOwningWorld;
    b2BodyId mPhysicsBody;

    TSharedPtr<sf::Texture> mTexture;
    sf::Sprite mSprite;
    
    TArray<b2ShapeId> mShapeIds;

    bool mHasBeganPlay;
    bool mPhysicsEnabled;

};


} // namespace nonsense