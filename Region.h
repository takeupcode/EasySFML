//
//  Region.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/11/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "SpriteAnimation.h"
#include "SpriteSheet.h"
#include "Window.h"

class Entity;

class Region
{
public:
    Region (std::shared_ptr<SpriteSheet> sheet, const sf::Vector2f & scale, const sf::Vector2u tileSize, unsigned int columns, unsigned int rows);
    
    Region (const Region &) = default;
    Region (Region &&) = default;
    
    Region & operator = (const Region &) = default;
    Region & operator = (Region &&) = default;
    
    sf::Vector2f scale () const
    {
        return mScale;
    }
    
    sf::Vector2u tileSize ()
    {
        return mTileSize;
    }
    
    unsigned int columns ()
    {
        return mRegionSize.x;
    }
    
    unsigned int rows ()
    {
        return mRegionSize.y;
    }
    
    sf::Vector2f position ()
    {
        return mPosition;
    }
    
    void setPosition (const sf::Vector2f & position)
    {
        mPosition = position;
    }
    
    float gravity ()
    {
        return mGravity;
    }
    
    void setGravity (float gravity)
    {
        mGravity = gravity;
    }
    
    bool addTileType (const std::string & typeName, const std::string & animationName, unsigned int beginningIndex = 0);
    
    void setTile (unsigned int x, unsigned int y, const std::string & typeName);
    
    void removeTile (unsigned int x, unsigned int y);

    void update (float elapsedSeconds);
    
    void draw (Window * window);
    
    void resolveCollisions (Entity * entity);
    
private:
    unsigned int index (unsigned int x, unsigned int y)
    {
        return x + y * mRegionSize.x;
    }
    
    sf::Vector2f mScale;
    sf::Vector2u mRegionSize;
    sf::Vector2u mTileSize;
    sf::Vector2f mPosition;
    float mGravity;
    std::shared_ptr<SpriteSheet> mSheet;
    std::unordered_map<std::string, std::unique_ptr<SpriteAnimation>> mTileTypes;
    std::vector<std::string> mTiles;
};
