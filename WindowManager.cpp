//
//  WindowManager.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/3/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Director.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "Window.h"

using namespace std;

WindowManager::WindowManager (Director * director)
: Directable(director)
{ }

bool WindowManager::addWindow (shared_ptr<Window> window)
{
    bool windowAdded = false;
    if (!mMainWindow)
    {
        mMainWindow = window;
        windowAdded = true;
    }
    else if (mWindows.find(window->identity()) == mWindows.end())
    {
        windowAdded = mWindows.emplace(window->identity(), window).second;
    }
    
    if (windowAdded)
    {
        window->loadTriggers();
    }
    
    return windowAdded;
}

void WindowManager::notify (EventParameter eventDetails)
{
    if (eventDetails.name() == EventManager::WindowClosed)
    {
    }
}

void WindowManager::handleInput ()
{
    if (mMainWindow)
    {
        mMainWindow->handleInput();
        
        for (auto & windowPosition: mWindows)
        {
            windowPosition.second->handleInput();
        }
    }
}

void WindowManager::loadTriggers ()
{
    director()->eventManager()->addSubscription(EventManager::WindowClosed, "WindowManager", shared_from_this());
}
