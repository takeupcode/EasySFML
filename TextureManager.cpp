//
//  TextureManager.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 9/3/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Director.h"
#include "TextureManager.h"

using namespace std;

TextureManager::TextureManager (Director * director)
: Directable(director)
{
}

sf::Texture * TextureManager::texture (const std::string & name) const
{
    sf::Texture * matchingTexture = nullptr;
    
    auto position = mTextures.find(name);
    if (position != mTextures.end())
    {
        matchingTexture = position->second.second.get();
    }
    
    return matchingTexture;
}

void TextureManager::loadTexture (const std::string & name, const std::string & path)
{
    auto position = mTextures.find(name);
    if (position != mTextures.end())
    {
        position->second.first++;
    }
    else
    {
        sf::Texture * newTexture = new sf::Texture();
        mTextures.emplace(name, make_pair(1, unique_ptr<sf::Texture>(newTexture)));
        
        if (!newTexture->loadFromFile(path))
        {
            throw runtime_error("Could not load texture.");
        }
    }
}

void TextureManager::releaseTexture (const std::string & name)
{
    auto position = mTextures.find(name);
    if (position != mTextures.end())
    {
        position->second.first--;
        if (position->second.first == 0)
        {
            mTextures.erase(position);
        }
    }
}

void TextureManager::notify (EventParameter eventDetails)
{
}

void TextureManager::loadTriggers ()
{
}
