//
//  WindowManager.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/3/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Directable.h"
#include "EventDetails.h"
#include "EventSubscriber.h"

class Window;

class WindowManager : public std::enable_shared_from_this<WindowManager>, public EventSubscriber<EventParameter>,
    public Directable
{
public:
    explicit WindowManager (Director * director);
    
    bool addWindow (std::shared_ptr<Window> window);
    
    std::shared_ptr<Window> mainWindow ()
    {
        return mMainWindow;
    }
    
private:
    friend class Director;
    
    void handleInput ();
    
    void loadTriggers ();
    
    void notify (EventParameter eventDetails) override;
    
    using Windows = std::unordered_map<int, std::shared_ptr<Window>>;
    
    std::shared_ptr<Window> mMainWindow;
    Windows mWindows;
};
