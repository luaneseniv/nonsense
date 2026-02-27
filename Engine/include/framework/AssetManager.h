#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace Nonsense
{

class AssetManager
{
public:
    static AssetManager& Get();
    TSharedPtr<sf::Texture> LoadTexture(const FString& texturePath);
    void CleanCycle();
    void SetContentDirectory(const FString& path);

protected:
    AssetManager();

private:
    static TUniquePtr<AssetManager> mAssetManager;
    TDict<FString, TSharedPtr<sf::Texture>> mLoadedTextures;
    FString mContentSourceDir;
    
};

} // namespace Nonsense