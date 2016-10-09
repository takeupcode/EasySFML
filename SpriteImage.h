//
//  SpriteImage.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 10/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <SFML/Graphics.hpp>

class SpriteImage
{
public:
    SpriteImage (const SpriteImage &) = default;
    SpriteImage (SpriteImage &&) = default;
    
    SpriteImage & operator = (const SpriteImage &) = default;
    SpriteImage & operator = (SpriteImage &&) = default;
    
    sf::Vector2u sheetPosition () const
    {
        return mSheetPosition;
    }
    
    unsigned int sheetX () const
    {
        return mSheetPosition.x;
    }
    
    unsigned int sheetY () const
    {
        return mSheetPosition.y;
    }
    
    sf::Vector2u sheetSize () const
    {
        return mSheetSize;
    }
    
    unsigned int sheetWidth () const
    {
        return mSheetSize.x;
    }
    
    unsigned int sheetHeight () const
    {
        return mSheetSize.y;
    }
    
    sf::Vector2u sourcePosition () const
    {
        return mSourcePosition;
    }
    
    unsigned int sourceX () const
    {
        return mSourcePosition.x;
    }
    
    unsigned int sourceY () const
    {
        return mSourcePosition.y;
    }
    
    sf::Vector2u sourceSize () const
    {
        return mSourceSize;
    }
    
    unsigned int sourceWidth () const
    {
        return mSourceSize.x;
    }
    
    unsigned int sourceHeight () const
    {
        return mSourceSize.y;
    }
    
    bool rotated () const
    {
        return mRotated;
    }
    
    bool trimmed () const
    {
        return mTrimmed;
    }
    
private:
    friend class SpriteSheet;
    
    SpriteImage (const sf::Vector2u & sheetPosition, const sf::Vector2u & sheetSize, const sf::Vector2u & sourcePosition, const sf::Vector2u & sourceSize,
                 bool rotated, bool trimmed)
    : mSheetPosition(sheetPosition), mSheetSize(sheetSize), mSourcePosition(sourcePosition), mSourceSize(sourceSize), mRotated(rotated), mTrimmed(trimmed)
    { }
    
    sf::Vector2u mSheetPosition;
    sf::Vector2u mSheetSize;
    sf::Vector2u mSourcePosition;
    sf::Vector2u mSourceSize;
    bool mRotated;
    bool mTrimmed;
};
