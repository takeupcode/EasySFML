//
//  SpriteAnimation.cpp
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/5/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation (std::shared_ptr<SpriteSheet> sheet, const std::string & animationName, const sf::Vector2f & scale)
: mScale(scale), mSheet(sheet), mCurrentIndex(0), mTimeInFrame(0), mUpdateSprite(true)
{
    mSprite.setScale(mScale);
    mCurrentAnimation = mSheet->animation(animationName);
    if (mCurrentAnimation)
    {
        mCurrentFrame = mCurrentAnimation->frame(mCurrentIndex);
        if (mCurrentFrame)
        {
            mSprite.setTexture(*mSheet->texture());
            mSprite.setTextureRect(mCurrentFrame->croppingRectangle());
            mSprite.setOrigin(mCurrentFrame->size().x / 2, mCurrentFrame->size().y);
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
        mSprite.setOrigin(mCurrentFrame->size().x / 2, mCurrentFrame->size().y);
    }
}
