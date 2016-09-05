//
//  Game.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Director.h"
#include "EventManager.h"
#include "Game.h"

using namespace std;

Game::Game (Director * director)
:Directable(director), mDone(false), mMaineWindowIdentity(0)
{
}

Game::~Game ()
{
}

void Game::loadTriggers ()
{
    director()->eventManager()->addSubscription(EventManager::WindowClosed, "Game", shared_from_this());
}

bool Game::isDone () const
{
    return mDone;
}

sf::Time Game::elapsed () const 
{
    return mElapsed;
}

void Game::restartClock ()
{
    mElapsed = mClock.restart();
    mFixedFrameTotal += mElapsed;
}

bool Game::isFixedFrameReady () const
{
    return mFixedFrameTotal.asSeconds() >= mFixedFrameTime;
}

void Game::completeFixedFrame ()
{
    mFixedFrameTotal -= sf::seconds(mFixedFrameTime);
}

void Game::quit ()
{
    mDone = true;
}

void Game::notify (EventParameter eventDetails)
{
    if (eventDetails.name() == EventManager::WindowClosed)
    {
        mDone = true;
    }
}
