//
//  SpriteSheet.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/5/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "FrameTag.h"
#include "FrameDefinition.h"
#include "AnimationDefinition.h"
    
class SpriteSheet
{
public:
    explicit SpriteSheet (const std::shared_ptr<sf::Texture> & texture)
    : mTexture(texture)
    { }
    
    SpriteSheet (const SpriteSheet &) = default;
    SpriteSheet (SpriteSheet &&) = default;
    
    SpriteSheet & operator = (const SpriteSheet &) = default;
    SpriteSheet & operator = (SpriteSheet &&) = default;
    
    std::shared_ptr<sf::Texture> texture () const
    {
        return mTexture;
    }
    
    AnimationDefinition * animation (const std::string & name)
    {
        auto position = mAnimations.find(name);
        if (position != mAnimations.end())
        {
            return position->second.get();
        }
        
        return nullptr;
    }
    
    AnimationDefinition * addAnimation (const std::string & name, const std::string & nextName)
    {
        auto result = mAnimations.emplace(name, std::unique_ptr<AnimationDefinition>(new AnimationDefinition(name, nextName)));
        AnimationDefinition * newAnimation = result.second ? result.first->second.get() : nullptr;
        
        if (newAnimation)
        {
            for (auto & item : mAnimations)
            {
                item.second->animationAdded(newAnimation);
            }
        }
        
        return newAnimation;
    }
    
    bool removeAnimation (const std::string & name)
    {
        return (mAnimations.erase(name) == 1);
    }
    
private:
    std::shared_ptr<sf::Texture> mTexture;
    std::unordered_map<std::string, std::unique_ptr<AnimationDefinition>> mAnimations;
};
