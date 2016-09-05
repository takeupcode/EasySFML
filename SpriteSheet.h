//
//  SpriteSheet.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/5/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

class SpriteSheet
{
public:
    SpriteSheet (std::shared_ptr<sf::Texture> & texture, const sf::Vector2u & size);
    ~SpriteSheet ();
    
    std::shared_ptr<sf::Texture> texture () const;
    sf::Vector2u size () const;
    
private:
    std::shared_ptr<sf::Texture> mTexture;
    sf::Vector2u & mSize;
};
