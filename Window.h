//
//  Window.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "Directable.h"
#include "EventDetails.h"
#include "EventSubscriber.h"

class EventManager;

class Window : public std::enable_shared_from_this<Window>, public EventSubscriber<EventParameter>,
    public Directable
{
public:
    Window (Director * director, int identity);
    Window (Director * director, int identity, const std::string & title, const sf::Vector2u & size);
    ~Window ();
    
    std::string title () const;
    sf::Vector2u size () const;
    int identity () const;
    bool isFullScreen () const;
    
    sf::View defaultView () const;
    sf::View view () const;
    void setView (const sf::View & view);

    void draw (const sf::Drawable & obj);
    void drawBegin ();
    void drawEnd ();
    
    void handleInput ();
    
protected:
    void notify (EventParameter eventDetails) override;
    
private:
    friend class WindowManager;
    
    void toggleFullScreen ();
    
    void loadTriggers ();
    
    void create ();
    void destroy ();
    
    sf::RenderWindow mWindow;
    int mIdentity;
    std::string mTitle;
    sf::Vector2u mSize;
    bool mFullScreen;
    std::shared_ptr<EventManager> mEventManager;
    bool mHasFocus;
};
