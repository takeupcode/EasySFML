//
//  EventManager.cpp
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 7/24/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "EventManager.h"
#include "Window.h"

using namespace std;

const string EventManager::WindowClosed = "WindowClosed";
const string EventManager::WindowResized = "WindowResized";
const string EventManager::WindowFocusLost = "WindowFocusLost";
const string EventManager::WindowFocusGained = "WindowFocusGained";
const string EventManager::WindowToggleFullScreen = "WindowToggleFullScreen";
const string EventManager::GamePause = "GamePause";
const string EventManager::GameContinue = "GameContinue";
const string EventManager::MenuSelect = "MenuSelect";
const string EventManager::MenuShow = "MenuShow";

EventManager::EventManager (Director * director)
: Directable(director)
{ }

bool EventManager::addTrigger (const Trigger & trigger)
{
    if (mTriggers.find(trigger.name()) != mTriggers.end())
    {
        return false;
    }
    
    return mTriggers.emplace(trigger.name(), unique_ptr<Trigger>(new Trigger(trigger))).second;
}

bool EventManager::removeTrigger (const std::string & name)
{
    auto position = mTriggers.find(name);
    if (position == mTriggers.end())
    {
        return false;
    }
    
    mTriggers.erase(position);
    
    return true;
}

bool EventManager::addSubscription (const std::string & triggerName, const std::string & identity,
                                      const std::shared_ptr<EventSubscriber<EventParameter>> & subscriber)
{
    auto position = mTriggers.find(triggerName);
    if (position == mTriggers.end())
    {
        return false;
    }
    
    auto event = position->second->eventMatchedEvent();
    event->connect(identity, subscriber);
    
    return true;
}

bool EventManager::removeSubscription (const std::string & triggerName, const std::string & identity)
{
    auto position = mTriggers.find(triggerName);
    if (position == mTriggers.end())
    {
        return false;
    }
    
    auto event = position->second->eventMatchedEvent();
    event->disconnect(identity);
    
    return true;
}

void EventManager::handleEvent (const Window & window, const sf::Event & event)
{
    for (auto & triggerPosition: mTriggers)
    {
        triggerPosition.second->handleEvent(window, event);
    }
}

void EventManager::handleCurrentStates (bool hasFocus)
{
    for (auto & triggerPosition: mTriggers)
    {
        triggerPosition.second->handleCurrentStates(hasFocus);
    }
}

void EventManager::createTriggers ()
{
    Trigger triggerWindowClosed {WindowClosed};
    Trigger triggerWindowResized {WindowResized};
    Trigger triggerWindowToggleFullScreen {WindowToggleFullScreen};
    Trigger triggerWindowFocusLost {WindowFocusLost};
    Trigger triggerWindowFocusGained {WindowFocusGained};
    Trigger triggerGamePause {GamePause};
    Trigger triggerGameContinue {GameContinue};
    Trigger triggerMenuSelect {MenuSelect};
    Trigger triggerMenuShow {MenuShow};
    
    Trigger * triggerPtr = &triggerWindowClosed;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::WindowClosed, 0, 0, -1});
    addTrigger(*triggerPtr);
    
    triggerPtr = &triggerWindowResized;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::WindowResized, 0, 0, -1});
    addTrigger(*triggerPtr);
    
    triggerPtr = &triggerWindowToggleFullScreen;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::KeyboardKeyPressed, 0, 0, sf::Keyboard::Key::F5});
    addTrigger(*triggerPtr);
    
    triggerPtr = &triggerWindowFocusLost;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::WindowFocusLost, 0, 0, -1});
    addTrigger(*triggerPtr);
    
    triggerPtr = &triggerWindowFocusGained;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::WindowFocusGained, 0, 0, -1});
    addTrigger(*triggerPtr);
    
    triggerPtr = &triggerGamePause;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::KeyboardKeyPressed, 0, 0, sf::Keyboard::Key::P});
    addTrigger(*triggerPtr);
    
    triggerPtr = &triggerGameContinue;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::KeyboardKeyPressed, 0, 0, -1});
    addTrigger(*triggerPtr);
    
    triggerPtr = &triggerMenuSelect;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::MouseButtonPressed, 0, 0, sf::Mouse::Button::Left});
    addTrigger(*triggerPtr);
    
    triggerPtr = &triggerMenuShow;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::KeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Escape});
    addTrigger(*triggerPtr);
}

void EventManager::loadTriggers ()
{
}
