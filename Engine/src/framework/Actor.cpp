#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

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
    if (IsActorOutOfWindow())
    {
        Destroy();
    }

}


void AActor::SetTexture(const FString& texturePath)
{
    // load the texture
    mTexture = AssetManager::Get().LoadTexture(texturePath);
    if(!mTexture)
    {
        mSprite.reset();
        return;
    }

    // construct the sprite
    int textureWidth = mTexture->getSize().x;
    int textureHeight = mTexture->getSize().y;
    mSprite.emplace(*mTexture.get(), sf::IntRect{sf::Vector2i{}, {textureWidth, textureHeight}});
    
    if (!mSprite) return;
    
    // update sprite's origin
    mPivot = {textureWidth * 0.5f, textureHeight * 0.5f};
    mSprite->setOrigin(mPivot);
}

void AActor::Render(sf::RenderWindow& window)
{
    if (IsPendingDestroy() && !mSprite)
        return;

    window.draw(*mSprite);
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

sf::FloatRect Nonsense::AActor::GetActorBound() const
{
    if (!mSprite)
        return sf::FloatRect{};
    
    return mSprite->getGlobalBounds();
}

bool AActor::IsActorOutOfWindow() const
{
    float windowWidth = GetCurrentWorld()->GetWindowSize().x;
    float windowHeight = GetCurrentWorld()->GetWindowSize().y;

    float boundWidth = GetActorBound().size.x;
    float boundHeight = GetActorBound().size.y;

    if (GetActorLocation().x < -boundWidth)
    {
        return true;
    }

    if (GetActorLocation().x > windowWidth + boundWidth)
    {
        return true;
    }

    if (GetActorLocation().y < boundHeight)
    {
        return true;
    }

    if (GetActorLocation().y > windowHeight + boundHeight)
    {
        return true;
    }

    return false;
}

} // namespace Nonsene


