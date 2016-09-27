//
//  Scene.cpp
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 8/21/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Director.h"
#include "EventManager.h"
#include "Scene.h"
#include "Window.h"

using namespace std;

Scene::Scene (Director * director, int identity, std::shared_ptr<Window> window, bool transparent, bool modal)
: Directable(director), mIdentity(identity), mWindow(window), mTransparent(transparent), mModal(modal), mActive(false),
mPreviousScene(nullptr), mNextScene(nullptr), mCreated(false), mDestroyed(false), mView(window->defaultView())
{ }

Scene::~Scene ()
{
}

void Scene::created ()
{
    if (!mDestroyed)
    {
        // Only create triggers the first time.
        createTriggers();
        
        // Update the view in case it changed before the scene gets created.
        mView.setSize(mWindow->size().x, mWindow->size().y);
        mView.setCenter(mWindow->size().x / 2, mWindow->size().y / 2);
    }
    
    loadTriggers();
    
    mCreated = true;
}

void Scene::createTriggers ()
{
}

void Scene::loadTriggers ()
{
    director()->eventManager()->addSubscription(EventManager::WindowResized, name(), shared_from_this());
}

void Scene::unloadTriggers ()
{
    director()->eventManager()->removeSubscription(EventManager::WindowResized, name());
}

void Scene::notify (EventParameter eventDetails)
{
    if (eventDetails.name() == EventManager::WindowResized)
    {
        mView.setSize(eventDetails.size().width, eventDetails.size().height);
        mView.setCenter(eventDetails.size().width / 2, eventDetails.size().height / 2);
    }
}
