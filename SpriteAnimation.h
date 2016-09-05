//
//  SpriteAnimation.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 9/5/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <SFML/Graphics.hpp>

class SpriteAnimation
{
public:
    SpriteAnimation (const sf::Vector2u & scale);
    ~SpriteAnimation ();
    
    sf::Vector2f scale () const;
    
private:
    sf::Vector2f & mScale;
};
