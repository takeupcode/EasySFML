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
mPreviousScene(nullptr), mNextScene(nullptr), mCreated(false), mView(window->defaultView())
{ }

Scene::~Scene ()
{
}
