//
//  Region.cpp
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/11/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Region.h"

using namespace std;

Region::Region (shared_ptr<SpriteSheet> sheet, const sf::Vector2f & scale, const sf::Vector2u tileSize, unsigned int columns, unsigned int rows)
: mScale(scale), mTileSize(tileSize), mRegionSize(columns, rows), mSheet(sheet)
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
    sf::IntRect tilesInView({static_cast<int>(floor((viewCenter.x - viewSize.x / 2) / mTileSize.x)),
        static_cast<int>(floor((viewCenter.y - viewSize.y / 2) / mTileSize.y)),
        static_cast<int>(ceil((viewCenter.x + viewSize.x / 2) / mTileSize.x)),
        static_cast<int>(ceil((viewCenter.y + viewSize.y / 2) / mTileSize.y))});
    for (int x = tilesInView.left; x <= tilesInView.left + tilesInView.width; ++x)
    {
        if (x >= mRegionSize.x)
        {
            continue;
        }
        for (int y = tilesInView.top; y <= tilesInView.top + tilesInView.height; ++y)
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
                    tile->setPosition({x * mTileSize.x + tile->size().x / 2, y * mTileSize.y + tile->size().y});
                    tile->draw(window);
                }
            }
        }
    }
}
