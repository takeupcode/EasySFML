//
//  TextureManager.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 9/3/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <map>

#include <SFML/Graphics.hpp>

#include "Directable.h"
#include "EventDetails.h"
#include "EventSubscriber.h"

class TextureManager : public std::enable_shared_from_this<TextureManager>, public EventSubscriber<EventParameter>,
public Directable
{
public:
    explicit TextureManager (Director * director);
    
    sf::Texture * texture (const std::string & name) const;
    
    void loadTexture (const std::string & name, const std::string & path);
    
    void releaseTexture (const std::string & name);
    
protected:
    void notify (EventParameter eventDetails) override;
    
private:
    friend class Director;
    
    void loadTriggers ();
    
    std::map<std::string, std::pair<int, std::unique_ptr<sf::Texture>>> mTextures;
};
