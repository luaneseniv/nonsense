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
    virtual void Destroy() override;
    
    virtual void Tick(float deltaTime);

    // These functions are called from World class
    void InternalBeginPlay();
    void InternalTick(float deltaTime);

    void Render(sf::RenderWindow& window); // this function is called from the world's Render()

    bool IsActorOutOfWindow() const;

    void SetEnablePhysics(bool enable, bool isBullet = false);

    virtual void OnActorBeginOverlap(AActor* other);
    virtual void OnActorEndOverlap(AActor* other);

protected:
    virtual void BeginPlay();

private: // functions
    void UpdateActorBound();
    void InitializePhysics(bool isBullet);
    void DeinitializePhysics();
    void UpdatePhysicsBodyTransform();

private: // Variables
    UWorld* mOwningWorld;
    b2BodyId mPhysicsBody;

    TSharedPtr<sf::Texture> mTexture;
    sf::Sprite mSprite;
    
    TArray<b2ShapeId> mShapeIds;

    bool mHasBeganPlay;
    bool mPhysicsEnabled;

public: // Getters Setters
    UWorld* GetCurrentWorld() const { return mOwningWorld; };
    sf::Vector2f GetActorLocation() const;
    float GetActorRotation() const; // return rotation in degrees
    sf::Vector2f GetActorForwardVector() const;
    sf::Vector2f GetActorRightVector() const;
    sf::FloatRect GetActorBound() const;
    sf::Vector2f GetActorPivot() const;
    float GetActorRadius() const { return GetActorBound().size.x * 0.25f; }

    void SetTexture(const FString& texturePath);
    void SetActorLocation(const sf::Vector2f& newLocation);
    void SetActorRotation(float newRotation);
    void AddActorLocationOffset(const sf::Vector2f& deltaLocation);
    void AddActorRotationOffset(float deltaRotation);



};


} // namespace nonsense