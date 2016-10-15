//
//  Entity.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/16/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <math.h>

#include <SFML/Graphics.hpp>

#include "Directable.h"
#include "Direction.h"
#include "EntityState.h"

class SpriteAnimation;
class Window;

class Entity : public Directable
{
public:
    Entity (Director * director, EntityState * state, const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2f & acceleration, const sf::Vector2f & scale, Direction dir = Direction::East)
    : Directable(director), mCurrentState(state), mNewState(nullptr), mPosition(position), mVelocity(velocity), mAcceleration(acceleration), mSize({0, 0}), mScale(scale), mSurfaceTile(nullptr), mDirection(dir)
    { }
    
    virtual ~Entity () = default;
    
    virtual void handleCommand (int command)
    {
        mCurrentState->handleCommand(command);
        handleStateChange();
    }
    
    virtual void update (float elapsedSeconds)
    {
        mCurrentState->update(elapsedSeconds);
        handleStateChange();
    }
    
    virtual void draw (Window * window) = 0;
    
    sf::Vector2f position () const
    {
        return mPosition;
    }
    
    void setPosition (const sf::Vector2f & position)
    {
        mPosition.x = position.x;
        
        // Use floor to reduce shakiness as the entity is falling each frame
        // due to gravity but tiles are trying to push the entity back up.
        mPosition.y = floorf(position.y);
    }
    
    void adjustPosition (const sf::Vector2f & delta)
    {
        mPosition.x += delta.x;
        mPosition.y += delta.y;
    }
    
    sf::Vector2f velocity () const
    {
        return mVelocity;
    }
    
    void setVelocity (const sf::Vector2f & velocity)
    {
        mVelocity = velocity;
    }
    
    void adjustVelocity (const sf::Vector2f delta)
    {
        mVelocity.x += delta.x;
        mVelocity.y += delta.y;
    }
    
    sf::Vector2f acceleration () const
    {
        return mAcceleration;
    }
    
    void setAcceleration (const sf::Vector2f & acceleration)
    {
        mAcceleration = acceleration;
    }
    
    void adjustAcceleration (const sf::Vector2f delta)
    {
        mAcceleration.x += delta.x;
        mAcceleration.y += delta.y;
    }
    
    sf::Vector2u size () const
    {
        return mSize;
    }
    
    void setSize (const sf::Vector2u & size)
    {
        mSize = size;
    }
    
    void adjustSize (const sf::Vector2u & delta)
    {
        mSize.x += delta.x;
        mSize.y += delta.y;
    }
    
    sf::Vector2f scale () const
    {
        return mScale;
    }
    
    sf::Vector2f scaledSize () const
    {
        return {mSize.x * mScale.x, mSize.y * mScale.y};
    }
    
    SpriteAnimation * surface () const
    {
        return mSurfaceTile;
    }
    
    void setSurface (SpriteAnimation * tile)
    {
        mSurfaceTile = tile;
    }
    
    Direction direction () const
    {
        return mDirection;
    }
    
    void setDirection (Direction dir)
    {
        mDirection = dir;
    }
    
    void setNewState (EntityState * state)
    {
        mNewState = state;
    }
    
protected:
    void handleStateChange ()
    {
        if (mNewState)
        {
            if (mNewState != mCurrentState)
            {
                mCurrentState->exit();
                mCurrentState = mNewState;
                mCurrentState->enter();
            }
            mNewState = nullptr;
        }
    }
    
    EntityState * mCurrentState;
    EntityState * mNewState;
    sf::Vector2f mPosition;
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
    sf::Vector2u mSize;
    sf::Vector2f mScale;
    SpriteAnimation * mSurfaceTile;
    Direction mDirection;
};
