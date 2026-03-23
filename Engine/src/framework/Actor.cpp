#include <box2d/box2d.h>

#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"


namespace Nonsense
{

AActor::AActor(UWorld* owningWorld, const FString& texturePath)
    : mOwningWorld{owningWorld},
    mHasBeganPlay{false},
    mPhysicsBody{b2_nullBodyId},
    mPhysicsEnabled{false},
    mTexture{AssetManager::Get().GetPlaceHolderTexture()},
    mSprite{*mTexture},
    mShapeIds{}
{
    SetTexture(texturePath);
    SetActorRotation(-90.0f);
}

AActor::~AActor()
{
    SetEnablePhysics(false);
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
    if (texturePath.empty())
        return;

    // loads the texture from provides path
    auto newTexture = AssetManager::Get().LoadTexture(texturePath);
    if(newTexture)
    {
        mTexture = newTexture;
        // Update the texture
        mSprite.setTexture(*mTexture);
    
        UpdateActorBound();
    }
}

void AActor::UpdateActorBound()
{
    if (mTexture)
    {
        // Update texture rect
        int textureWidth = mTexture->getSize().x;
        int textureHeight = mTexture->getSize().y;
        mSprite.setTextureRect({{0, 0}, {textureWidth, textureHeight}});
        
        // update sprite's origin
        sf::Vector2f pivot = {textureWidth * 0.5f, textureHeight * 0.5f};
        mSprite.setOrigin(pivot);
    }
}

void AActor::Render(sf::RenderWindow& window)
{
    if (IsPendingDestroy())
        return;

    window.draw(mSprite);
    
    
// Debug: Draw the collider shapes for all actors
    const int shapeCount = b2Body_GetShapeCount(mPhysicsBody);
    
    if (shapeCount > 0)
    {
        for (int i = 0; i < shapeCount; ++i)
        {
            b2Transform bodyTransform = b2Body_GetTransform(mPhysicsBody);
    
            mShapeIds.resize(shapeCount);
    
            b2Body_GetShapes(mPhysicsBody, mShapeIds.data(), shapeCount);
    
            b2Circle circle = b2Shape_GetCircle(mShapeIds[i]);
            b2Vec2 pos = b2TransformPoint(bodyTransform, circle.center);
            float radius = circle.radius;
    
            PhysicsSystem::Get().DrawDebugCircle(pos, radius, b2_colorWhite, &window);
        }
    }

// end debug
}

void AActor::SetActorLocation(const sf::Vector2f& newLocation)
{
        mSprite.setPosition(newLocation);
        UpdatePhysicsBodyTransform();
}

void AActor::SetActorRotation(float newRotation)
{
        mSprite.setRotation(sf::degrees(newRotation));
        UpdatePhysicsBodyTransform();
}

void AActor::AddActorLocationOffset(const sf::Vector2f& deltaLocation)
{
        SetActorLocation(GetActorLocation() + deltaLocation);
}

void AActor::AddActorRotationOffset(float deltaRotation)
{
    SetActorRotation(GetActorRotation() + deltaRotation);
}

sf::Vector2f AActor::GetActorLocation() const
{
    return mSprite.getPosition();
}

float AActor::GetActorRotation() const
{
    return mSprite.getRotation().asDegrees();
}

sf::Vector2f AActor::GetActorForwardVector() const
{
    return RotationToVector<sf::Vector2f>(GetActorRotation());
}

sf::Vector2f AActor::GetActorRightVector() const
{
    return RotationToVector<sf::Vector2f>(GetActorRotation() + 90.0f);
}

sf::FloatRect Nonsense::AActor::GetActorBound() const
{
    return mSprite.getGlobalBounds();
    
}

sf::Vector2f AActor::GetActorPivot() const
{
    return mSprite.getOrigin();
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

    if (GetActorLocation().y < - boundHeight)
    {
        return true;
    }

    if (GetActorLocation().y > windowHeight + boundHeight)
    {
        return true;
    }

    return false;
}

void AActor::SetEnablePhysics(bool enable, bool isBullet)
{
    mPhysicsEnabled = enable;

    if (mPhysicsEnabled)
    {
        InitializePhysics(isBullet);
    }
    else
    {
        DeinitializePhysics();
    }

}

void AActor::OnActorBeginOverlap(AActor *other)
{
    NS_LOG("overlapped");
}

void AActor::OnActorEndOverlap(AActor *other)
{
    NS_LOG("End overlapped");
}

void AActor::InitializePhysics(bool isBullet)
{
    if (B2_IS_NULL(mPhysicsBody))
    {
        mPhysicsBody = PhysicsSystem::Get().AddListener(this, isBullet);
    }
}

void AActor::DeinitializePhysics()
{
    if (B2_IS_NON_NULL(mPhysicsBody))
    {
        PhysicsSystem::Get().RemoveListener(mPhysicsBody);
    }
}

void AActor::UpdatePhysicsBodyTransform()
{
    if (b2Body_IsValid(mPhysicsBody))
    {
        b2Vec2 position = ToB2Vector2(GetActorLocation());
        ScaleVector(position, PhysicsSystem::Get().GetPhysicsScale());
    
        b2Rot rotation = b2MakeRot(Deg2Rad(GetActorRotation()));
    
        // NS_LOG("UpdatePhysicsBodyTransform: actor=%p actorPos=%f,%f scaled=%f,%f bodyId=%u",
            //    this, GetActorLocation().x, GetActorLocation().y, position.x, position.y, mPhysicsBody);

        b2Body_SetTransform(mPhysicsBody, position, rotation);

        b2Vec2 bodyPos = b2Body_GetPosition(mPhysicsBody);
        // NS_LOG("After SetTransform: bodyPos=%f,%f", bodyPos.x, bodyPos.y);
    }

}

} // namespace Nonsene


