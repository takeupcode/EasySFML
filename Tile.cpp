//
//  Tile.cpp
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 10/16/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Tile.h"

Tile::Tile (std::shared_ptr<SpriteSheet> sheet, const std::string & animationName, const sf::Vector2f & scale, unsigned int beginningIndex)
: mAnimation(new SpriteAnimation(sheet, animationName, scale, beginningIndex))
{
}
