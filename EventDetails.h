//
//  EventDetails.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 8/20/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

class EventDetails;
using EventParameter = const EventDetails &;

struct WindowEvent
{
    int mIdentity;
};

class EventDetails
{
public:
    explicit EventDetails (const std::string & name)
    : mData(new EventDetailsData(name))
    { }
    
    EventDetails (const EventDetails & src)
    : mData(new EventDetailsData(*src.mData))
    { }
    
    EventDetails (EventDetails && src)
    : mData(src.mData.release())
    { }
    
    ~EventDetails ()
    { }
    
    void swap (EventDetails & other)
    {
        std::unique_ptr<EventDetailsData> thisData(mData.release());
        std::unique_ptr<EventDetailsData> otherData(other.mData.release());
        
        mData.reset(otherData.release());
        other.mData.reset(thisData.release());
    }
    
    EventDetails & operator = (const EventDetails & rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        
        *mData = *rhs.mData;
        
        return *this;
    }
    
    EventDetails & operator = (EventDetails && rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        
        mData.reset(rhs.mData.release());
        
        return *this;
    }
    
    std::string name () const
    {
        return mData->mName;
    }
    
    bool hasWindow () const
    {
        return mData->mHasWindow;
    }
    
    WindowEvent window () const
    {
        return mData->mWindow;
    }
    
    void setWindow (const WindowEvent & event)
    {
        mData->mWindow = event;
        mData->mHasWindow = true;
    }
    
    bool hasSize () const
    {
        return mData->mHasSize;
    }
    
    sf::Event::SizeEvent size () const
    {
        return mData->mSize;
    }
    
    void setSize (const sf::Event::SizeEvent & event)
    {
        mData->mSize = event;
        mData->mHasSize = true;
    }
    
    bool hasKey () const
    {
        return mData->mHasKey;
    }
    
    sf::Event::KeyEvent key () const
    {
        return mData->mKey;
    }
    
    void setKey (const sf::Event::KeyEvent & event)
    {
        mData->mKey = event;
        mData->mHasKey = true;
    }
    
    bool hasText () const
    {
        return mData->mHasText;
    }
    
    sf::Event::TextEvent text () const
    {
        return mData->mText;
    }
    
    void setText (const sf::Event::TextEvent & event)
    {
        mData->mText = event;
        mData->mHasText = true;
    }
    
    bool hasMouseMove () const
    {
        return mData->mHasMouseMove;
    }
    
    sf::Event::MouseMoveEvent mouseMove () const
    {
        return mData->mMouseMove;
    }
    
    void setMouseMove (const sf::Event::MouseMoveEvent & event)
    {
        mData->mMouseMove = event;
        mData->mHasMouseMove = true;
    }
    
    bool hasMouseButton () const
    {
        return mData->mHasMouseButton;
    }
    
    sf::Event::MouseButtonEvent mouseButton () const
    {
        return mData->mMouseButton;
    }
    
    void setMouseButton (const sf::Event::MouseButtonEvent & event)
    {
        mData->mMouseButton = event;
        mData->mHasMouseButton = true;
    }
    
    bool hasMouseWheel () const
    {
        return mData->mHasMouseWheel;
    }
    
    sf::Event::MouseWheelScrollEvent mouseWheel () const
    {
        return mData->mMouseWheel;
    }
    
    void setMouseWheel (const sf::Event::MouseWheelScrollEvent & event)
    {
        mData->mMouseWheel = event;
        mData->mHasMouseWheel = true;
    }
    
    bool hasJoystickMove () const
    {
        return mData->mHasJoystickMove;
    }
    
    sf::Event::JoystickMoveEvent joystickMove () const
    {
        return mData->mJoystickMove;
    }
    
    void setJoystickMove (const sf::Event::JoystickMoveEvent & event)
    {
        mData->mJoystickMove = event;
        mData->mHasJoystickMove = true;
    }
    
    bool hasJoystickButton () const
    {
        return mData->mHasJoystickButton;
    }
    
    sf::Event::JoystickButtonEvent joystickButton () const
    {
        return mData->mJoystickButton;
    }
    
    void setJoystickButton (const sf::Event::JoystickButtonEvent & event)
    {
        mData->mJoystickButton = event;
        mData->mHasJoystickButton = true;
    }
    
    bool hasJoystickConnect () const
    {
        return mData->mHasJoystickConnect;
    }
    
    sf::Event::JoystickConnectEvent joystickConnect () const
    {
        return mData->mJoystickConnect;
    }
    
    void setJoystickConnect (const sf::Event::JoystickConnectEvent & event)
    {
        mData->mJoystickConnect = event;
        mData->mHasJoystickConnect = true;
    }
    
    bool hasTouch () const
    {
        return mData->mHasTouch;
    }
    
    sf::Event::TouchEvent touch () const
    {
        return mData->mTouch;
    }
    
    void setTouch (const sf::Event::TouchEvent & event)
    {
        mData->mTouch = event;
        mData->mHasTouch = true;
    }
    
    bool hasSensor () const
    {
        return mData->mHasSensor;
    }
    
    sf::Event::SensorEvent sensor () const
    {
        return mData->mSensor;
    }
    
    void setSensor (const sf::Event::SensorEvent & event)
    {
        mData->mSensor = event;
        mData->mHasSensor = true;
    }
    
    void clear ()
    {
        mData->mHasWindow = false;
        mData->mHasSize = false;
        mData->mHasKey = false;
        mData->mHasText = false;
        mData->mHasMouseMove = false;
        mData->mHasMouseButton = false;
        mData->mHasMouseWheel = false;
        mData->mHasJoystickMove = false;
        mData->mHasJoystickButton = false;
        mData->mHasJoystickConnect = false;
        mData->mHasTouch = false;
        mData->mHasSensor = false;
    }
    
private:
    struct EventDetailsData
    {
        std::string mName;
        bool mHasWindow;
        bool mHasSize;
        bool mHasKey;
        bool mHasText;
        bool mHasMouseMove;
        bool mHasMouseButton;
        bool mHasMouseWheel;
        bool mHasJoystickMove;
        bool mHasJoystickButton;
        bool mHasJoystickConnect;
        bool mHasTouch;
        bool mHasSensor;
        WindowEvent mWindow;
        sf::Event::SizeEvent mSize;
        sf::Event::KeyEvent mKey;
        sf::Event::TextEvent mText;
        sf::Event::MouseMoveEvent mMouseMove;
        sf::Event::MouseButtonEvent mMouseButton;
        sf::Event::MouseWheelScrollEvent mMouseWheel;
        sf::Event::JoystickMoveEvent mJoystickMove;
        sf::Event::JoystickButtonEvent mJoystickButton;
        sf::Event::JoystickConnectEvent mJoystickConnect;
        sf::Event::TouchEvent mTouch;
        sf::Event::SensorEvent mSensor;
        
        EventDetailsData (const std::string & name)
        : mName(name), mHasWindow(false), mHasSize(false), mHasKey(false), mHasText(false),
        mHasMouseMove(false), mHasMouseButton(false), mHasMouseWheel(false),
        mHasJoystickMove(false), mHasJoystickButton(false), mHasJoystickConnect(false),
        mHasTouch(false), mHasSensor(false)
        { }
        
        EventDetailsData (const EventDetailsData & src)
        : mName(src.mName), mHasWindow(src.mHasWindow), mHasSize(src.mHasSize), mHasKey(src.mHasKey), mHasText(src.mHasText),
        mHasMouseMove(src.mHasMouseMove), mHasMouseButton(src.mHasMouseButton), mHasMouseWheel(src.mHasMouseWheel),
        mHasJoystickMove(src.mHasJoystickMove), mHasJoystickButton(src.mHasJoystickButton), mHasJoystickConnect(src.mHasJoystickConnect),
        mHasTouch(src.mHasTouch), mHasSensor(src.mHasSensor)
        {
            if (mHasWindow)
            {
                mWindow = src.mWindow;
            }
            if (mHasSize)
            {
                mSize = src.mSize;
            }
            if (mHasKey)
            {
                mKey = src.mKey;
            }
            if (mHasText)
            {
                mText = src.mText;
            }
            if (mHasMouseMove)
            {
                mMouseMove = src.mMouseMove;
            }
            if (mHasMouseButton)
            {
                mMouseButton = src.mMouseButton;
            }
            if (mHasMouseWheel)
            {
                mMouseWheel = src.mMouseWheel;
            }
            if (mHasJoystickMove)
            {
                mJoystickMove = src.mJoystickMove;
            }
            if (mHasJoystickButton)
            {
                mJoystickButton = src.mJoystickButton;
            }
            if (mHasJoystickConnect)
            {
                mJoystickConnect = src.mJoystickConnect;
            }
            if (mHasTouch)
            {
                mTouch = src.mTouch;
            }
            if (mHasSensor)
            {
                mSensor = src.mSensor;
            }
        }
        
        ~EventDetailsData ()
        { }
        
        EventDetailsData & operator = (const EventDetailsData & rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }
            
            mName = rhs.mName;
            
            mHasWindow = rhs.mHasWindow;
            if (mHasWindow)
            {
                mWindow = rhs.mWindow;
            }
            mHasSize = rhs.mHasSize;
            if (mHasSize)
            {
                mSize = rhs.mSize;
            }
            mHasKey = rhs.mHasKey;
            if (mHasKey)
            {
                mKey = rhs.mKey;
            }
            mHasText = rhs.mHasText;
            if (mHasText)
            {
                mText = rhs.mText;
            }
            mHasMouseMove = rhs.mHasMouseMove;
            if (mHasMouseMove)
            {
                mMouseMove = rhs.mMouseMove;
            }
            mHasMouseButton = rhs.mHasMouseButton;
            if (mHasMouseButton)
            {
                mMouseButton = rhs.mMouseButton;
            }
            mHasMouseWheel = rhs.mHasMouseWheel;
            if (mHasMouseWheel)
            {
                mMouseWheel = rhs.mMouseWheel;
            }
            mHasJoystickMove = rhs.mHasJoystickMove;
            if (mHasJoystickMove)
            {
                mJoystickMove = rhs.mJoystickMove;
            }
            mHasJoystickButton = rhs.mHasJoystickButton;
            if (mHasJoystickButton)
            {
                mJoystickButton = rhs.mJoystickButton;
            }
            mHasJoystickConnect = rhs.mHasJoystickConnect;
            if (mHasJoystickConnect)
            {
                mJoystickConnect = rhs.mJoystickConnect;
            }
            mHasTouch = rhs.mHasTouch;
            if (mHasTouch)
            {
                mTouch = rhs.mTouch;
            }
            mHasSensor = rhs.mHasSensor;
            if (mHasSensor)
            {
                mSensor = rhs.mSensor;
            }
            return *this;
        }
    };
    
    std::unique_ptr<EventDetailsData> mData;
};
