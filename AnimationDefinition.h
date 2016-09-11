//
//  AnimationDefinition.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/9/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "FrameDefinition.h"

class AnimationDefinition
{
public:
    AnimationDefinition (const AnimationDefinition &) = default;
    AnimationDefinition (AnimationDefinition &&) = default;
    
    AnimationDefinition & operator = (const AnimationDefinition &) = default;
    AnimationDefinition & operator = (AnimationDefinition &&) = default;
    
    std::string name () const
    {
        return mName;
    }
    
    AnimationDefinition * next () const
    {
        return mNextAnimation;
    }
    
    unsigned int frameCount ()
    {
        return static_cast<unsigned int>(mFrames.size());
    }
    
    FrameDefinition * frame (unsigned int index)
    {
        if (index < mFrames.size())
        {
            return mFrames[index].get();
        }
        
        return nullptr;
    }
    
    FrameDefinition * addFrame (float time, const sf::Vector2i & topLeft, const sf::Vector2i & size)
    {
        mFrames.emplace_back(std::unique_ptr<FrameDefinition>(new FrameDefinition(time, topLeft, size)));
        
        return mFrames[mFrames.size() - 1].get();
    }
    
    bool removeFrame (unsigned int index)
    {
        if (index < mFrames.size())
        {
            mFrames.erase(mFrames.begin() + index);
            return true;
        }
        
        return false;
    }
    
private:
    friend class SpriteSheet;
    
    AnimationDefinition (const std::string & animationName, const std::string & nextAnimationName)
    : mName(animationName), mNextName(nextAnimationName), mNextAnimation(nullptr)
    { }
    
    void animationAdded (AnimationDefinition * animation)
    {
        if (animation != nullptr && animation->name() == mNextName)
        {
            mNextAnimation = animation;
        }
    }
    
    std::string mName;
    std::string mNextName;
    AnimationDefinition * mNextAnimation;
    std::vector<std::unique_ptr<FrameDefinition>> mFrames;
};
