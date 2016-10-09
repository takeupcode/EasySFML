//
//  SpriteAnimation.cpp
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/5/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation (std::shared_ptr<SpriteSheet> sheet, const std::string & animationName, const sf::Vector2f & scale, unsigned int beginningIndex)
: mScale(scale), mCurrentAnimation(nullptr), mCurrentFrame(nullptr), mCurrentIndex(beginningIndex), mTimeInFrame(0), mUpdateSprite(false)
{
    mSprite.setScale(mScale);
    
    addAnimation(sheet, animationName);
    setAnimation(animationName, beginningIndex);
}

void SpriteAnimation::addAnimation (std::shared_ptr<SpriteSheet> sheet, const std::string & animationName)
{
    mAnimations.emplace(animationName, sheet);
}

void SpriteAnimation::setAnimation (const std::string & animationName, unsigned int beginningIndex)
{
    auto position = mAnimations.find(animationName);
    if (position != mAnimations.end())
    {
        SpriteSheet * sheet = position->second.get();
        AnimationDefinition * newAnimation = sheet->animation(animationName);
        if (newAnimation && newAnimation != mCurrentAnimation)
        {
            mCurrentAnimation = newAnimation;
            mCurrentIndex = beginningIndex;
            if (mCurrentSheetName != sheet->name())
            {
                mSprite.setTexture(*sheet->texture());
                mCurrentSheetName = sheet->name();
            }
        }
    }
    
    if (mCurrentAnimation)
    {
        mCurrentFrame = mCurrentAnimation->frame(mCurrentIndex);
        if (mCurrentFrame)
        {
            mSprite.setTextureRect(mCurrentFrame->croppingRectangle());
            mSprite.setOrigin(mCurrentFrame->width() / 2 - mCurrentFrame->croppingX(), mCurrentFrame->height() - mCurrentFrame->croppingY());
            mUpdateSprite = true;
        }
        else
        {
            mUpdateSprite = false;
        }
    }
    else
    {
        mUpdateSprite = false;
    }
}

void SpriteAnimation::update (float elapsedSeconds)
{
    if (!mUpdateSprite)
    {
        return;
    }
    mTimeInFrame += elapsedSeconds;
    if (mTimeInFrame > mCurrentFrame->time())
    {
        mTimeInFrame -= mCurrentFrame->time();
        ++mCurrentIndex;
        
        if (mCurrentIndex < mCurrentAnimation->frameCount())
        {
            mCurrentFrame = mCurrentAnimation->frame(mCurrentIndex);
        }
        else
        {
            mCurrentAnimation = mCurrentAnimation->next();
            if (!mCurrentAnimation)
            {
                // We reached the end of the animation. The sprite can still
                // be drawn with the last frame. It just won't change anymore.
                mUpdateSprite = false;
                return;
            }
            mCurrentIndex = 0;
            mCurrentFrame = mCurrentAnimation->frame(mCurrentIndex);
            if (!mCurrentFrame)
            {
                // This will cause the sprite to stop drawing.
                mUpdateSprite = false;
                return;
            }
        }
        mSprite.setTextureRect(mCurrentFrame->croppingRectangle());
        mSprite.setOrigin(mCurrentFrame->width() / 2 - mCurrentFrame->croppingX(), mCurrentFrame->height() - mCurrentFrame->croppingY());
    }
}
