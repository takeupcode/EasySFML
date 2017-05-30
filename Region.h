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

#include "SpriteSheet.h"
#include "Tile.h"
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
    
    sf::Vector2f tileScaledSize ()
    {
        return {mTileSize.x * mScale.x, mTileSize.y * mScale.y};
    }
    
    unsigned int columns ()
    {
        return mColumns;
    }
    
    unsigned int rows ()
    {
        return mRows;
    }
    
    float width ()
    {
        return mScale.x * mColumns * mTileSize.x;
    }
    
    float height ()
    {
        return mScale.y * mRows * mTileSize.y;
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
        return x + y * mColumns;
    }
    
    struct CollisionData
    {
        Tile * mTile;
        sf::Rect<unsigned int> mTileRect;
        unsigned int mCollisionArea;
    };
    
    void detectCollisions (const sf::Rect<unsigned int> & entityRect);
    
    static bool sortCollisions (const CollisionData & item1, const CollisionData & item2);
    
    sf::Vector2f mScale;
    unsigned int mColumns;
    unsigned int mRows;
    sf::Vector2u mTileSize;
    float mGravity;
    std::shared_ptr<SpriteSheet> mSheet;
    std::unordered_map<std::string, std::unique_ptr<Tile>> mTileTypes;
    std::vector<std::string> mTiles;
    std::vector<CollisionData> mCollisions;
};
