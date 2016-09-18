//
//  Region.cpp
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/11/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Entity.h"
#include "Region.h"

using namespace std;

Region::Region (shared_ptr<SpriteSheet> sheet, const sf::Vector2f & scale, const sf::Vector2u tileSize, unsigned int columns, unsigned int rows)
: mScale(scale), mTileSize(tileSize), mRegionSize(columns, rows), mSheet(sheet), mGravity(0.0f)
{
    mTiles.resize(mRegionSize.x * mRegionSize.y);
}

bool Region::addTileType (const string & typeName, const string & animationName, unsigned int beginningIndex)
{
    auto result = mTileTypes.emplace(typeName, unique_ptr<SpriteAnimation>(new SpriteAnimation(mSheet, animationName, mScale, beginningIndex)));
    return result.second;
}

void Region::setTile (unsigned int x, unsigned int y, const string & typeName)
{
    mTiles[index(x, y)] = typeName;
}

void Region::removeTile (unsigned int x, unsigned int y)
{
    mTiles[index(x, y)] = "";
}

void Region::update (float elapsedSeconds)
{
    for (auto & tileType: mTileTypes)
    {
        tileType.second->update(elapsedSeconds);
    }
}

void Region::draw (Window * window)
{
    sf::View view = window->view();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    
    unsigned int fromX = floorf((viewCenter.x - viewSize.x / 2) / mTileSize.x);
    unsigned int toX = ceilf((viewCenter.x + viewSize.x / 2) / mTileSize.x);
    unsigned int fromY = floorf((viewCenter.y - viewSize.y / 2) / mTileSize.y);
    unsigned int toY = ceilf((viewCenter.y + viewSize.y / 2) / mTileSize.y);
    
    for (unsigned int x = fromX; x <= toX; ++x)
    {
        if (x >= mRegionSize.x)
        {
            continue;
        }
        for (unsigned int y = fromY; y <= toY; ++y)
        {
            if (y >= mRegionSize.y)
            {
                continue;
            }
            string tileType = mTiles[index(x, y)];
            if (!tileType.empty())
            {
                auto tilePosition = mTileTypes.find(tileType);
                if (tilePosition != mTileTypes.end())
                {
                    SpriteAnimation * tile = tilePosition->second.get();
                    tile->setPosition({x * mTileSize.x + tile->scaledSize().x / 2, y * mTileSize.y + tile->scaledSize().y});
                    tile->draw(window);
                }
            }
        }
    }
}

void Region::resolveCollisions (Entity * entity)
{
    sf::Rect<unsigned int> entityRect;
    entityRect.left = floorf(entity->position().x - entity->scaledSize().x / 2);
    entityRect.top = floorf(entity->position().y - entity->scaledSize().y);
    entityRect.width = ceilf(entity->scaledSize().x);
    entityRect.height = ceilf(entity->scaledSize().y);
    
    detectCollisions(entityRect);
    
    SpriteAnimation * surface = nullptr;
    for (auto & data: mCollisions)
    {
        // Calculate the entity position each time because it can change.
        entityRect.left = floorf(entity->position().x - entity->scaledSize().x / 2);
        entityRect.top = floorf(entity->position().y - entity->scaledSize().y);
        
        sf::Rect<unsigned int> collisionRect;
        if (!entityRect.intersects(data.mTileRect, collisionRect))
        {
            continue;
        }
        
        // Use width vs. height to determine if the collision should be resolved from the top or bottom vs.
        // from the left or right.
        if (collisionRect.width >= collisionRect.height)
        {
            // Check which side was hit. Add one so we're not trying to compare exact float values.
            if (collisionRect.top < data.mTileRect.top + 1)
            {
                entity->setPosition({entity->position().x, static_cast<float>(data.mTileRect.top)});
                entity->setVelocity({entity->velocity().x, 0.0f});
                if (!surface)
                {
                    surface = data.mTile;
                }
            }
            else
            {
                entity->setPosition({entity->position().x, static_cast<float>(data.mTileRect.top + data.mTileRect.height + entityRect.height)});
                entity->setVelocity({entity->velocity().x, 0.0f});
            }
        }
        else
        {
            // Check which side was hit. Add one so we're not trying to compare exact float values.
            if (collisionRect.left < data.mTileRect.left + 1)
            {
                entity->setPosition({static_cast<float>(data.mTileRect.left) - entity->scaledSize().x / 2, entity->position().y});
            }
            else
            {
                entity->setPosition({static_cast<float>(data.mTileRect.left + data.mTileRect.width + 1) + entity->scaledSize().x / 2, entity->position().y});
            }
            entity->setVelocity({0.0f, entity->velocity().y});
        }
    }
    entity->setSurface(surface);
}

void Region::detectCollisions (const sf::Rect<unsigned int> & entityRect)
{
    mCollisions.clear();
    
    unsigned int fromX = entityRect.left / mTileSize.x;
    unsigned int toX = (entityRect.left + entityRect.width) / mTileSize.x;
    unsigned int fromY = entityRect.top / mTileSize.y;
    unsigned int toY = (entityRect.top + entityRect.height) / mTileSize.y;
    
    
    for (unsigned int x = fromX; x <= toX; ++x)
    {
        if (x >= mRegionSize.x)
        {
            continue;
        }
        for (unsigned int y = fromY; y <= toY; ++y)
        {
            if (y >= mRegionSize.y)
            {
                continue;
            }
            string tileType = mTiles[index(x, y)];
            if (!tileType.empty())
            {
                auto tilePosition = mTileTypes.find(tileType);
                if (tilePosition != mTileTypes.end())
                {
                    SpriteAnimation * tile = tilePosition->second.get();
                    
                    sf::Rect<unsigned int> tileRect;
                    tileRect.left = x * mTileSize.x;
                    tileRect.top = y * mTileSize.y;
                    tileRect.width = ceilf(tile->scaledSize().x);
                    tileRect.height = ceilf(tile->scaledSize().y);
                    
                    sf::Rect<unsigned int> collisionRect;
                    if (entityRect.intersects(tileRect, collisionRect))
                    {
                        CollisionData data;
                        data.mTile = tile;
                        data.mTileRect = tileRect;
                        data.mCollisionArea = collisionRect.width * collisionRect.height;
                        // There's no need to store the collision rect because it just needs
                        // to be recalculated anyway because it can change as the collision
                        // gets resolved.
                        
                        mCollisions.push_back(data);
                    }
                }
            }
        }
    }
    if (mCollisions.size() > 1)
    {
        sort(mCollisions.begin(), mCollisions.end(), sortCollisions);
    }
}

bool Region::sortCollisions (const CollisionData & item1, const CollisionData & item2)
{
    return item1.mCollisionArea > item2.mCollisionArea;
}
