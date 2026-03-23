#include "framework/AssetManager.h"

namespace Nonsense
{

AssetManager& AssetManager::Get()
{
    static AssetManager instance;

    return instance;
}

TSharedPtr<sf::Texture> AssetManager::LoadTexture(const FString& texturePath)
{
    // Checks if the texture was loaded
    auto foundTexture = mLoadedTextures.find(texturePath);
    if(foundTexture != mLoadedTextures.end())
    {
        return foundTexture->second;
    }

    // Creates new texture and adds it to the pool
    TSharedPtr<sf::Texture> newTexture{ new sf::Texture };
    if(newTexture->loadFromFile(mContentSourceDir + texturePath))
    {
        mLoadedTextures.insert({texturePath, newTexture});
        return newTexture;
    }

    return TSharedPtr<sf::Texture>{nullptr};
}

TSharedPtr<sf::Texture> AssetManager::GetPlaceHolderTexture() const
{
    if (!mPlaceHolderTexture)
    {
        sf::Image img(sf::Vector2u{16, 16}, sf::Color::White);
        mPlaceHolderTexture = MakeSharePtr<sf::Texture>(img);
    }

    return mPlaceHolderTexture;
}

void AssetManager::CleanCycle()
{
    NS_LOG("Running asset cleaning.");
    
    // simple asset cleaning method
    // this is not a good solution for the performance
    for (auto it = mLoadedTextures.begin(); it != mLoadedTextures.end();)
    {
        if (it->second.unique())
        {
            NS_LOG("Removing texture: %s", it->first.c_str());
            it = mLoadedTextures.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void AssetManager::SetContentDirectory(const FString& path)
{
    mContentSourceDir = path;
}

AssetManager::AssetManager() : mContentSourceDir{}
{

}

AssetManager::~AssetManager()
{

}

} // namespace nonsense