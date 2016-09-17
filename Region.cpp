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
    
    sf::Rect<unsigned int> tilesInView;
    tilesInView.left = floor((viewCenter.x - viewSize.x / 2) / mTileSize.x);
    tilesInView.top = floor((viewCenter.y - viewSize.y / 2) / mTileSize.y);
    tilesInView.width = ceil((viewCenter.x + viewSize.x / 2) / mTileSize.x);
    tilesInView.height = ceil((viewCenter.y + viewSize.y / 2) / mTileSize.y);
    for (unsigned int x = tilesInView.left; x <= tilesInView.left + tilesInView.width; ++x)
    {
        if (x >= mRegionSize.x)
        {
            continue;
        }
        for (unsigned int y = tilesInView.top; y <= tilesInView.top + tilesInView.height; ++y)
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
    entityRect.left = entity->position().x - entity->scaledSize().x / 2;
    entityRect.top = entity->position().y - entity->scaledSize().y;
    entityRect.width = entity->scaledSize().x;
    entityRect.height = entity->scaledSize().y;
    
    for (unsigned int x = 0; x < mRegionSize.x; ++x)
    {
        for (unsigned int y = 0; y < mRegionSize.y; ++y)
        {
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
                    tileRect.width = tile->scaledSize().x;
                    tileRect.height = tile->scaledSize().y;
                    
                    sf::Rect<unsigned int> intersectRect;
                    if (entityRect.intersects(tileRect, intersectRect))
                    {
                        if (intersectRect.width > intersectRect.height)
                        {
                            entity->setPosition({entity->position().x, static_cast<float>(tileRect.top)});
                            entity->setVelocity({entity->velocity().x, 0.0f});
                        }
                        else
                        {
                            if (intersectRect.left + intersectRect.left + intersectRect.width < tileRect.left + tileRect.left + tileRect.width)
                            {
                                entity->setPosition({static_cast<float>(tileRect.left) - entity->scaledSize().x / 2, entity->position().y});
                            }
                            else
                            {
                                entity->setPosition({static_cast<float>(tileRect.left + tileRect.width) + entity->scaledSize().x / 2, entity->position().y});
                            }
                            entity->setVelocity({0.0f, entity->velocity().y});
                        }
                        return;
                    }
                }
            }
        }
    }
}
