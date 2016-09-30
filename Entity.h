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

class SpriteAnimation;
class Window;

class Entity : public Directable
{
public:
    Entity (Director * director, const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2f & acceleration, const sf::Vector2u & size, const sf::Vector2f & scale)
    : Directable(director), mPosition(position), mVelocity(velocity), mAcceleration(acceleration), mSize(size), mScale(scale), mSurfaceTile(nullptr)
    { }
    
    virtual ~Entity () = default;
    
    virtual void update (float elapsedSeconds) = 0;
    
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
    
protected:
    sf::Vector2f mPosition;
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
    sf::Vector2u mSize;
    sf::Vector2f mScale;
    SpriteAnimation * mSurfaceTile;
};
