#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace Nonsense
{

class AssetManager
{
public:
    static AssetManager& Get();
    
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
    AssetManager(AssetManager&&) = delete;
    AssetManager& operator=(AssetManager&&) = delete;

    TSharedPtr<sf::Texture> LoadTexture(const FString& texturePath);
    void CleanCycle();
    void SetContentDirectory(const FString& path);


private:
    AssetManager();
    ~AssetManager();
    TDict<FString, TSharedPtr<sf::Texture>> mLoadedTextures;
    FString mContentSourceDir;
    
};

} // namespace Nonsense