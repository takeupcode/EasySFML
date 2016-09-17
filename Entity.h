//
//  Entity.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/16/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <SFML/Graphics.hpp>

class Window;

class Entity
{
public:
    Entity (const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2u & size, const sf::Vector2f & scale)
    : mPosition(position), mVelocity(velocity), mSize(size), mScale(scale)
    { }
    
    virtual ~Entity () = default;
    
    virtual void move (const sf::Vector2f delta, float elapsedSeconds) = 0;
    
    virtual void draw (Window * window) = 0;
    
    sf::Vector2f position () const
    {
        return mPosition;
    }
    
    void setPosition (const sf::Vector2f & position)
    {
        mPosition = position;
    }
    
    sf::Vector2f velocity () const
    {
        return mVelocity;
    }
    
    void setVelocity (const sf::Vector2f & velocity)
    {
        mVelocity = velocity;
    }
    
    sf::Vector2u size () const
    {
        return mSize;
    }
    
    void setSize (const sf::Vector2u & size)
    {
        mSize = size;
    }
    
    sf::Vector2f scale () const
    {
        return mScale;
    }
    
    sf::Vector2f scaledSize () const
    {
        return {mSize.x * mScale.x, mSize.y * mScale.y};
    }
    
private:
    sf::Vector2f mPosition;
    sf::Vector2f mVelocity;
    sf::Vector2u mSize;
    sf::Vector2f mScale;
};
