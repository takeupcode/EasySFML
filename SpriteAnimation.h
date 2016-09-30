//
//  SpriteAnimation.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/5/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "SpriteSheet.h"
#include "Window.h"

class SpriteAnimation
{
public:
    SpriteAnimation (std::shared_ptr<SpriteSheet> sheet, const std::string & animationName, const sf::Vector2f & scale, unsigned int beginningIndex = 0);
    
    SpriteAnimation (const SpriteAnimation &) = default;
    SpriteAnimation (SpriteAnimation &&) = default;
    
    SpriteAnimation & operator = (const SpriteAnimation &) = default;
    SpriteAnimation & operator = (SpriteAnimation &&) = default;
    
    sf::Vector2f scale () const
    {
        return mScale;
    }
    
    sf::Vector2f position ()
    {
        return mSprite.getPosition();
    }
    
    sf::Vector2f scaledSize ()
    {
        if (mCurrentFrame)
        {
            sf::Vector2u unscaledSize = mCurrentFrame->size();
            return {unscaledSize.x * mScale.x, unscaledSize.y * mScale.y};
        }
        
        return {0.0f, 0.0f};
    }
    
    void setPosition (const sf::Vector2f & position)
    {
        mSprite.setPosition(position);
    }
    
    void setAnimation (const std::string & animationName);
    
    FrameTag * tag (const std::string & name)
    {
        if (mCurrentFrame)
        {
            return mCurrentFrame->tag(name);
        }
        return nullptr;
    }
    
    void update (float elapsedSeconds);

    void draw (Window * window)
    {
        if (mCurrentFrame)
        {
            window->draw(mSprite);
        }
    }

private:
    sf::Vector2f mScale;
    std::shared_ptr<SpriteSheet> mSheet;
    AnimationDefinition * mCurrentAnimation;
    FrameDefinition * mCurrentFrame;
    unsigned int mCurrentIndex;
    float mTimeInFrame;
    sf::Sprite mSprite;
    bool mUpdateSprite;
};
