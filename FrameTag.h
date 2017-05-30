//
//  FrameTag.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/9/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class FrameTag
{
public:
    enum class TagType
    {
        BoolTag,
        IntTag,
        FloatTag,
        StringTag,
        RectangleTag
    };
    
    FrameTag (const FrameTag &) = default;
    FrameTag (FrameTag &&) = default;
    
    FrameTag & operator = (const FrameTag &) = default;
    FrameTag & operator = (FrameTag &&) = default;
    
    TagType type () const
    {
        return mType;
    }
    
    bool boolValue () const
    {
        return mBoolValue;
    }
    
    int intValue () const
    {
        return mIntValue;
    }
    
    float floatValue () const
    {
        return mFloatValue;
    }
    
    std::string stringValue () const
    {
        return mStringValue;
    }
    
    sf::IntRect rectangleValue () const
    {
        return mRectangleValue;
    }
    
private:
    friend class FrameDefinition;
    
    FrameTag (bool value)
    : mType(TagType::BoolTag), mBoolValue(value)
    { }
    
    FrameTag (int value)
    : mType(TagType::IntTag), mIntValue(value)
    { }
    
    FrameTag (float value)
    : mType(TagType::FloatTag), mFloatValue(value)
    { }
    
    FrameTag (const std::string & value)
    : mType(TagType::StringTag), mStringValue(value)
    { }
    
    FrameTag (const sf::IntRect & value)
    : mType(TagType::RectangleTag), mRectangleValue(value)
    { }
    
    TagType mType;
    union
    {
        bool mBoolValue;
        int mIntValue;
        float mFloatValue;
        sf::IntRect mRectangleValue;
    };
    std::string mStringValue;
};
