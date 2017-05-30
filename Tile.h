//
//  Tile.hpp
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 10/16/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "SpriteAnimation.h"
#include "SpriteSheet.h"
#include "Window.h"

class Entity;

class Tile
{
public:
    Tile (std::shared_ptr<SpriteSheet> sheet, const std::string & animationName, const sf::Vector2f & scale, unsigned int beginningIndex = 0);
    ~Tile () = default;
    
    Tile (const Tile &) = default;
    Tile (Tile &&) = default;
    
    Tile & operator = (const Tile &) = default;
    Tile & operator = (Tile &&) = default;
    
    sf::Vector2f scaledSize ()
    {
        return mAnimation->scaledSize();
    }
    
    void setPosition (const sf::Vector2f & position)
    {
        mAnimation->setPosition(position);
    }
    
    FrameTag * tag (const std::string & name)
    {
        return mAnimation->tag(name);
    }
    
    void update (float elapsedSeconds)
    {
        mAnimation->update(elapsedSeconds);
    }
    
    void draw (Window * window)
    {
        mAnimation->draw(window);
    }
    
protected:
    std::unique_ptr<SpriteAnimation> mAnimation;
};
