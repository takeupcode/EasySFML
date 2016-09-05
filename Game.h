//
//  Game.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "Directable.h"
#include "EventDetails.h"
#include "EventSubscriber.h"

class Window;

class Game : public std::enable_shared_from_this<Game>, public EventSubscriber<EventParameter>,
    public Directable
{
public:
    virtual ~Game ();
    
    bool isDone () const;
    sf::Time elapsed () const;
    void restartClock ();
    bool isFixedFrameReady () const;
    void completeFixedFrame ();
    
    void quit ();
    
protected:
    friend class Director;
    
    explicit Game (Director * director);
    
    virtual void loadTriggers ();

    virtual void registerScenes () = 0;

    virtual void setInitialScenes () = 0;

    virtual std::shared_ptr<Window> createMainWindow () const = 0;
    virtual int mainWindowIdentity () const = 0;
    
    void notify (EventParameter eventDetails) override;
    
private:
    const float mFixedFrameTime = 1.0f / 60.0f;
    
    sf::Clock mClock;
    sf::Time mElapsed;
    sf::Time mFixedFrameTotal;
    bool mDone;
    int mMaineWindowIdentity;
};
