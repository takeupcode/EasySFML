//
//  FrameDefinition.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/9/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "FrameTag.h"
#include "SpriteImage.h"

class FrameDefinition
{
public:
    FrameDefinition (const FrameDefinition &) = default;
    FrameDefinition (FrameDefinition &&) = default;
    
    FrameDefinition & operator = (const FrameDefinition &) = default;
    FrameDefinition & operator = (FrameDefinition &&) = default;
    
    float time () const
    {
        return mTime;
    }
    
    sf::Vector2u size () const
    {
        return mImage->sourceSize();
    }
    
    unsigned int width () const
    {
        return mImage->sourceWidth();
    }
    
    unsigned int height () const
    {
        return mImage->sourceHeight();
    }
    
    sf::IntRect croppingRectangle () const
    {
        return sf::IntRect(mImage->sheetX(), mImage->sheetY(), mImage->sheetWidth(), mImage->sheetHeight());
    }
    
    sf::Vector2u croppingOffset () const
    {
        return sf::Vector2u(mImage->sourceX(), mImage->sourceY());
    }
    
    unsigned int croppingX () const
    {
        return mImage->sourceX();
    }
    
    unsigned int croppingY () const
    {
        return mImage->sourceY();
    }
    
    FrameTag * tag (const std::string & name)
    {
        auto position = mTags.find(name);
        if (position != mTags.end())
        {
            return position->second.get();
        }
        
        return nullptr;
    }
    
    FrameTag * addTag (const std::string & name, bool value)
    {
        FrameTag tag(value);
        return addFrameTag(name, tag);
    }
    
    FrameTag * addTag (const std::string & name, int value)
    {
        FrameTag tag(value);
        return addFrameTag(name, tag);
    }

    FrameTag * addTag (const std::string & name, float value)
    {
        FrameTag tag(value);
        return addFrameTag(name, tag);
    }
    
    FrameTag * addTag (const std::string & name, const std::string & value)
    {
        FrameTag tag(value);
        return addFrameTag(name, tag);
    }
    
    FrameTag * addTag (const std::string & name, const sf::IntRect & value)
    {
        FrameTag tag(value);
        return addFrameTag(name, tag);
    }
    
    bool removeTag (const std::string & name)
    {
        return (mTags.erase(name) == 1);
    }
    
private:
    friend class AnimationDefinition;
    
    FrameDefinition (float time, const SpriteImage * image)
    : mTime(time), mImage(image)
    { }
    
    FrameTag * addFrameTag (const std::string & name, const FrameTag & tag)
    {
        auto result = mTags.emplace(name, std::unique_ptr<FrameTag>(new FrameTag(tag)));
        return result.second ? result.first->second.get() : nullptr;
    }
    
    float mTime;
    const SpriteImage * mImage;
    std::unordered_map<std::string, std::unique_ptr<FrameTag>> mTags;
};
