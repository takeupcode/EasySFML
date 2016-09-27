//
//  Scene.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 7/31/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "Directable.h"
#include "EventDetails.h"
#include "EventSubscriber.h"

class Window;
class SceneManager;

class Scene : public std::enable_shared_from_this<Scene>, public EventSubscriber<EventParameter>,
    public Directable
{
public:
    virtual ~Scene ();

    int identity () const
    {
        return mIdentity;
    }
    
    virtual std::string name () const = 0;

    bool isTransparent () const
    {
        return mTransparent;
    }
    
    bool isModal () const
    {
        return mModal;
    }
    
    bool isActive () const
    {
        return mActive;
    }
    
    virtual void created ();
    
    virtual void destroyed ()
    {
        unloadTriggers();
        
        mDestroyed = true;
    }
    
    virtual void activated ()
    {
        mActive = true;
    }
    
    virtual void deactivated ()
    {
        mActive = false;
    }
    
    bool hasBeenRecreated ()
    {
        return mCreated && mDestroyed;
    }
    
    sf::View view () const
    {
        return mView;
    }
    
    virtual void update (float elapsedSeconds) = 0;
    virtual void render () = 0;
    
protected:
    friend class SceneManager;
    
    Scene (Director * director, int identity, std::shared_ptr<Window> window, bool transparent, bool modal);
    
    virtual void createTriggers ();
    virtual void loadTriggers ();
    virtual void unloadTriggers ();
    
    void notify (EventParameter eventDetails) override;
    
    std::shared_ptr<Window> mWindow;
    int mIdentity;
    bool mTransparent;
    bool mModal;
    bool mActive;
    bool mCreated;
    bool mDestroyed;
    Scene * mPreviousScene;
    Scene * mNextScene;
    sf::View mView;
};
