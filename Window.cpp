//
//  Window.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Director.h"
#include "EventManager.h"
#include "Window.h"

using namespace std;

Window::Window (Director * director, int identity)
: Directable(director), mIdentity(identity), mTitle("GameWindow"), mSize(800, 600), mFullScreen(false), mEventManager(director->eventManager()),
mHasFocus(true)
{
    create();
}

Window::Window (Director * director, int identity, const std::string & title, const sf::Vector2u & size)
: Directable(director), mIdentity(identity), mTitle(title), mSize(size), mFullScreen(false), mEventManager(director->eventManager()),
mHasFocus(true)
{
    create();
}

Window::~Window ()
{
    destroy();
}

void Window::drawBegin ()
{
    mWindow.clear(sf::Color::Black);
}

void Window::drawEnd ()
{
    mWindow.display();
}

void Window::draw (const sf::Drawable & obj)
{
    mWindow.draw(obj);
}

void Window::handleInput ()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mEventManager->handleEvent(*this, event);
    }
    
    mEventManager->handleCurrentStates(mHasFocus);
}

void Window::toggleFullScreen ()
{
    mFullScreen = !mFullScreen;
    destroy();
    create();
}

std::string Window::title () const
{
    return mTitle;
}

sf::Vector2u Window::size () const
{
    return mSize;
}

int Window::identity () const
{
    return mIdentity;
}

bool Window::isFullScreen () const
{
    return mFullScreen;
}

sf::View Window::defaultView () const
{
    return mWindow.getDefaultView();
}

sf::View Window::view () const
{
    return mWindow.getView();
}

void Window::setView (const sf::View & view)
{
    mWindow.setView(view);
}

void Window::notify (EventParameter eventDetails)
{
    if  (eventDetails.name() == EventManager::WindowToggleFullScreen)
    {
        toggleFullScreen();
    }
    else if (eventDetails.name() == EventManager::WindowFocusLost)
    {
        mHasFocus = false;
    }
    else if (eventDetails.name() == EventManager::WindowFocusGained)
    {
        mHasFocus = true;
    }
}

void Window::loadTriggers()
{
    mEventManager->addSubscription(EventManager::WindowToggleFullScreen, "Window", shared_from_this());
    mEventManager->addSubscription(EventManager::WindowFocusLost, "Window", shared_from_this());
    mEventManager->addSubscription(EventManager::WindowFocusGained, "Window", shared_from_this());
}

void Window::create ()
{
    auto style = mFullScreen ? sf::Style::Fullscreen : sf::Style::Default;
    mWindow.create({mSize.x, mSize.y}, mTitle, style);
    mWindow.setFramerateLimit(60);
}

void Window::destroy ()
{
    mWindow.close();
}
