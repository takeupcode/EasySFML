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
    explicit SpriteSheet (const std::string & name, const std::shared_ptr<sf::Texture> & texture)
    : mName(name), mTexture(texture)
    { }
    
    SpriteSheet (const SpriteSheet &) = default;
    SpriteSheet (SpriteSheet &&) = default;
    
    SpriteSheet & operator = (const SpriteSheet &) = default;
    SpriteSheet & operator = (SpriteSheet &&) = default;
    
    std::string name () const
    {
        return mName;
    }
    
    std::shared_ptr<sf::Texture> texture () const
    {
        return mTexture;
    }
    
    AnimationDefinition * animation (const std::string & animationName)
    {
        auto position = mAnimations.find(animationName);
        if (position != mAnimations.end())
        {
            return position->second.get();
        }
        
        return nullptr;
    }
    
    AnimationDefinition * addAnimation (const std::string & animationName, const std::string & nextAnimationName)
    {
        auto result = mAnimations.emplace(animationName, std::unique_ptr<AnimationDefinition>(new AnimationDefinition(animationName, nextAnimationName)));
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
    
    bool removeAnimation (const std::string & animationName)
    {
        return (mAnimations.erase(animationName) == 1);
    }
    
private:
    std::string mName;
    std::shared_ptr<sf::Texture> mTexture;
    std::unordered_map<std::string, std::unique_ptr<AnimationDefinition>> mAnimations;
};
