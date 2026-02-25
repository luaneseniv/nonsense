#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"

namespace Nonsense
{

AActor::AActor(UWorld* owningWorld, const FString& texturePath)
    : mOwningWorld{owningWorld},
    mHasBeganPlay{false},
    mSprite{},
    mTexture{nullptr}
{
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
    mTexture = AssetManager::Get().LoadTexture(texturePath);
    if(!mTexture) return;

    mSprite.emplace(*mTexture);

    int textureWidth = mTexture->getSize().x;
    int textureHeight = mTexture->getSize().y;
    mSprite.value().setTextureRect(sf::IntRect{sf::Vector2i{}, {textureWidth, textureHeight}});
}

void AActor::Render(sf::RenderWindow& window)
{
    window.draw(mSprite.value());
}


} // namespace Nonsene