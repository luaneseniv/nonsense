#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"

namespace Nonsense
{

AActor::AActor(UWorld* owningWorld, const FString& texturePath)
    : mOwningWorld{owningWorld},
    mHasBeganPlay{false},
    mSprite{},
    mTexture{},
    mPivot{}
{
    SetTexture(texturePath);
}

AActor::~AActor()
{
    NS_LOG("Actor has been destroyed!");
}

void AActor::InternalBeginPlay()
{
    if(!mHasBeganPlay)
    {
        mHasBeganPlay = true;
        BeginPlay();
    }
}

void AActor::InternalTick(float deltaTime)
{
    Tick(deltaTime);
}

void AActor::BeginPlay()
{
    
    NS_LOG("Actor Begin Play");
    
}

void AActor::Tick(float deltaTime)
{

}

void AActor::SetTexture(const FString& texturePath)
{
    // load the texture
    mTexture = AssetManager::Get().LoadTexture(texturePath);
    if(!mTexture) return;

    // init the sprite
    mSprite.emplace(*mTexture);

    // Update texture for sprite
    int textureWidth = mTexture->getSize().x;
    int textureHeight = mTexture->getSize().y;
    mSprite->setTextureRect(sf::IntRect{sf::Vector2i{}, {textureWidth, textureHeight}});

    // update sprite's origin
    mPivot = {textureWidth * 0.5f, textureHeight * 0.5f};
    mSprite->setOrigin(mPivot);
}

void AActor::Render(sf::RenderWindow& window)
{
    if (IsPendingDestroy())
        return;

    window.draw(mSprite.value());
}

void AActor::SetActorLocation(const sf::Vector2f& newLocation)
{
    mSprite->setPosition(newLocation);
}

void AActor::SetActorRotation(float newRotation)
{
    mSprite->setRotation(sf::degrees(newRotation));
}

void AActor::AddActorLocationOffset(const sf::Vector2f& deltaLocation)
{
    mSprite->setPosition(GetActorLocation() + deltaLocation);
}

void AActor::AddActorRotationOffset(float deltaRotation)
{
    mSprite->setRotation(sf::degrees(GetActorRotation() + deltaRotation));
}

sf::Vector2f AActor::GetActorLocation() const
{
    return mSprite->getPosition();
}

float AActor::GetActorRotation() const
{
    return (mSprite->getRotation().asDegrees());
}

sf::Vector2f AActor::GetActorForwardVector() const
{
    return RotationToVector(GetActorRotation());
}

sf::Vector2f AActor::GetActorRightVector() const
{
    return RotationToVector(GetActorRotation() + 90.0f);
}
} // namespace Nonsene