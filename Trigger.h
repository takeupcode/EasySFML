//
//  Trigger.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "EventDetails.h"
#include "EventPublisher.h"
#include "Window.h"

class Trigger
{
public:
    enum class TriggerType
    {
        // These types map to event types.
        WindowClosed = sf::Event::Closed,
        WindowResized = sf::Event::Resized,
        WindowFocusLost = sf::Event::LostFocus,
        WindowFocusGained = sf::Event::GainedFocus,
        KeyboardTextEntered = sf::Event::TextEntered,
        KeyboardKeyPressed = sf::Event::KeyPressed,
        KeyboardKeyReleased = sf::Event::KeyReleased,
        MouseWheelScrolled = sf::Event::MouseWheelScrolled,
        MouseButtonPressed = sf::Event::MouseButtonPressed,
        MouseButtonReleased = sf::Event::MouseButtonReleased,
        MouseMoved = sf::Event::MouseMoved,
        MouseEntered = sf::Event::MouseEntered,
        MouseDeparted = sf::Event::MouseLeft,
        JoystickButtonPressed = sf::Event::JoystickButtonPressed,
        JoystickButtonReleased = sf::Event::JoystickButtonReleased,
        JoystickMoved = sf::Event::JoystickMoved,
        JoystickConnected = sf::Event::JoystickConnected,
        JoystickDisconnected = sf::Event::JoystickDisconnected,
        TouchBegan = sf::Event::TouchBegan,
        TouchMoved = sf::Event::TouchMoved,
        TouchEnded = sf::Event::TouchEnded,
        SensorChanged = sf::Event::SensorChanged,
        
        // And these types represent current states.
        CurrentKeyboardKeyPressed = sf::Event::Count + 1,
        CurrentMouseButtonPressed,
        CurrentJoystickButtonPressed
    };

    class TriggerPoint
    {
    public:
        explicit TriggerPoint (TriggerType type, int device = 0, int axis = 0, int code = 0)
        : mData(new TriggerPointData(type, device, axis, code))
        { }
        
        TriggerPoint (const TriggerPoint & src)
        : mData(new TriggerPointData(*src.mData))
        { }
        
        TriggerPoint (TriggerPoint && src)
        : mData(src.mData.release())
        { }
        
        ~TriggerPoint ()
        { }
        
        void swap (TriggerPoint & other)
        {
            std::unique_ptr<TriggerPointData> thisData(mData.release());
            std::unique_ptr<TriggerPointData> otherData(other.mData.release());
            
            mData.reset(otherData.release());
            other.mData.reset(thisData.release());
        }
        
        TriggerPoint & operator = (const TriggerPoint & rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }
            
            *mData = *rhs.mData;
            
            return *this;
        }
        
        TriggerPoint & operator = (TriggerPoint && rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }
            
            mData.reset(rhs.mData.release());
            
            return *this;
        }

        TriggerType type () const
        {
            return mData->mType;
        }
        
        int device () const
        {
            return mData->mDevice;
        }
        
        int axis () const
        {
            return mData->mAxis;
        }
        
        int code () const
        {
            return mData->mCode;
        }
        
        bool isEventType () const
        {
            return static_cast<unsigned int>(mData->mType) < static_cast<unsigned int>(sf::Event::Count);
        }

    private:
        struct TriggerPointData
        {
            TriggerType mType;
            
            // The device, axis, and code mean different things depending on the type.
            // For event processing, these can be set to -1 to match any event. But for
            // real-time detection, -1 is not allowed.
            
            // Joystick: This is the device id. Set to -1 to mean any joystick event.
            int mDevice;
            
            // This means different things depending on the type:
            // MouseWheel: This is the wheel code. Set to -1 to mean any wheel event.
            // JoystickMove: This is the axis code. Set to -1 to mean any axis event.
            int mAxis;
            
            // This means different things depending on the type:
            // KeyboardKey: This is the key code. Set to -1 to mean any key event.
            // MouseButton: This is the button code. Set to -1 to mean any button event.
            // JoystickButton: This is the button code. Set to -1 to mean any button event.
            // Touch: This is the finger code. Set to -1 to mean any finger event.
            // Sensor: This is the sensor code. Set to -1 to mean any sensor event.
            int mCode;
            
            TriggerPointData (TriggerType type, int device, int axis, int code)
            : mType(type), mDevice(device), mAxis(axis), mCode(code)
            { }
            
            TriggerPointData (const TriggerPointData & src)
            : mType(src.mType), mDevice(src.mDevice), mAxis(src.mAxis), mCode(src.mCode)
            { }
            
            ~TriggerPointData ()
            { }
            
            TriggerPointData & operator = (const TriggerPointData & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }
                
                mType = rhs.mType;
                mDevice = rhs.mDevice;
                mAxis = rhs.mAxis;
                mCode = rhs.mCode;
                
                return *this;
            }
        };
        
        std::unique_ptr<TriggerPointData> mData;
    };
    
    using TriggerPoints = std::vector<TriggerPoint>;
    using TriggerEvent = EventPublisher<EventParameter>;

    Trigger (const std::string & name)
    : mData(new TriggerData(name))
    { }
    
    Trigger (const Trigger & src)
    : mData(new TriggerData(*src.mData))
    { }
    
    Trigger (Trigger && src)
    : mData(src.mData.release())
    { }
    
    ~Trigger ()
    { }
    
    void swap (Trigger & other)
    {
        std::unique_ptr<TriggerData> thisData(mData.release());
        std::unique_ptr<TriggerData> otherData(other.mData.release());
        
        mData.reset(otherData.release());
        other.mData.reset(thisData.release());
    }
    
    Trigger & operator = (const Trigger & rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        
        *mData = *rhs.mData;
        
        return *this;
    }
    
    Trigger & operator = (Trigger && rhs)
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
    
    void addTriggerPoint (const TriggerPoint & triggerPoint)
    {
        mData->mTriggerPoints.push_back(triggerPoint);
    }
    
    std::shared_ptr<TriggerEvent> eventMatchedEvent ()
    {
        return mData->mEventMatchedEvent;
    }
    
    void handleEvent (const Window & window, const sf::Event & event)
    {
        TriggerType sfmlEventType = static_cast<TriggerType>(event.type);
        for (auto & triggerPoint: mData->mTriggerPoints)
        {
            if (triggerPoint.type() != sfmlEventType)
            {
                continue;
            }
            if (sfmlEventType == TriggerType::WindowClosed ||
                sfmlEventType == TriggerType::WindowFocusLost ||
                sfmlEventType == TriggerType::WindowFocusGained)
            {
                if (triggerPoint.code() == -1 || triggerPoint.code() == window.identity())
                {
                    WindowEvent windowEvent;
                    windowEvent.mIdentity = window.identity();
                    
                    mData->mDetails.setWindow(windowEvent);
                    ++mData->mTriggerPointMatches;
                }
                break;
            }
            else if (sfmlEventType == TriggerType::WindowResized)
            {
                if (triggerPoint.code() == -1 || triggerPoint.code() == window.identity())
                {
                    WindowEvent windowEvent;
                    windowEvent.mIdentity = window.identity();
                    
                    mData->mDetails.setWindow(windowEvent);
                    mData->mDetails.setSize(event.size);
                    ++mData->mTriggerPointMatches;
                }
                break;
            }
            else if (sfmlEventType == TriggerType::KeyboardKeyPressed ||
                sfmlEventType == TriggerType::KeyboardKeyReleased)
            {
                if (triggerPoint.code() == -1 || triggerPoint.code() == event.key.code)
                {
                    mData->mDetails.setKey(event.key);
                    ++mData->mTriggerPointMatches;
                }
                break;
            }
            else if (sfmlEventType == TriggerType::MouseButtonPressed ||
                     sfmlEventType == TriggerType::MouseButtonReleased)
            {
                if (triggerPoint.code() == -1 || triggerPoint.code() == event.mouseButton.button)
                {
                    mData->mDetails.setMouseButton(event.mouseButton);
                    ++mData->mTriggerPointMatches;
                }
                break;
            }
            else if (sfmlEventType == TriggerType::MouseWheelScrolled)
            {
                if (triggerPoint.axis() == -1 || triggerPoint.axis() == event.mouseWheelScroll.wheel)
                {
                    mData->mDetails.setMouseWheel(event.mouseWheelScroll);
                    ++mData->mTriggerPointMatches;
                }
                break;
            }
            else if (sfmlEventType == TriggerType::JoystickButtonPressed ||
                     sfmlEventType == TriggerType::JoystickButtonReleased)
            {
                if (triggerPoint.device() == -1 || triggerPoint.device() == event.joystickButton.joystickId)
                {
                    if (triggerPoint.code() == -1 || triggerPoint.code() == event.joystickButton.button)
                    {
                        mData->mDetails.setJoystickButton(event.joystickButton);
                        ++mData->mTriggerPointMatches;
                    }
                }
                break;
            }
            else if (sfmlEventType == TriggerType::JoystickMoved)
            {
                if (triggerPoint.device() == -1 || triggerPoint.device() == event.joystickMove.joystickId)
                {
                    mData->mDetails.setJoystickMove(event.joystickMove);
                    ++mData->mTriggerPointMatches;
                }
                break;
            }
            else if (sfmlEventType == TriggerType::JoystickConnected ||
                     sfmlEventType == TriggerType::JoystickDisconnected)
            {
                if (triggerPoint.device() == -1 || triggerPoint.device() == event.joystickConnect.joystickId)
                {
                    mData->mDetails.setJoystickConnect(event.joystickConnect);
                    ++mData->mTriggerPointMatches;
                }
                break;
            }
            else if (sfmlEventType == TriggerType::TouchBegan ||
                     sfmlEventType == TriggerType::TouchMoved ||
                     sfmlEventType == TriggerType::TouchEnded)
            {
                if (triggerPoint.code() == -1 || triggerPoint.code() == event.touch.finger)
                {
                    mData->mDetails.setTouch(event.touch);
                    ++mData->mTriggerPointMatches;
                }
                break;
            }
            else if (sfmlEventType == TriggerType::SensorChanged)
            {
                if (triggerPoint.code() == -1 || triggerPoint.code() == event.sensor.type)
                {
                    mData->mDetails.setSensor(event.sensor);
                    ++mData->mTriggerPointMatches;
                }
                break;
            }
            else
            {
                if (sfmlEventType == TriggerType::KeyboardTextEntered)
                {
                    mData->mDetails.setText(event.text);
                }
                if (sfmlEventType == TriggerType::MouseMoved)
                {
                    mData->mDetails.setMouseMove(event.mouseMove);
                }
                
                ++mData->mTriggerPointMatches;
                break;
            }
        }
    }

    void handleCurrentStates (bool checkTriggers)
    {
        if (checkTriggers)
        {
            for (auto & triggerPoint: mData->mTriggerPoints)
            {
                if (triggerPoint.type() == TriggerType::CurrentKeyboardKeyPressed)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(triggerPoint.code())))
                    {
                        sf::Event::KeyEvent event;
                        event.alt = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RAlt);
                        event.control = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);
                        event.shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);
                        event.system = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LSystem) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RSystem);
                        event.code = sf::Keyboard::Key(triggerPoint.code());
                        
                        mData->mDetails.setKey(event);
                        ++mData->mTriggerPointMatches;
                    }
                    continue;
                }
                else if (triggerPoint.type() == TriggerType::CurrentMouseButtonPressed)
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button(triggerPoint.code())))
                    {
                        sf::Event::MouseButtonEvent event;
                        sf::Vector2i position = sf::Mouse::getPosition();
                        event.x = position.x;
                        event.y = position.y;
                        event.button = sf::Mouse::Button(triggerPoint.code());
                        
                        mData->mDetails.setMouseButton(event);
                        ++mData->mTriggerPointMatches;
                    }
                    continue;
                }
                else if (triggerPoint.type() == TriggerType::CurrentJoystickButtonPressed)
                {
                    if (sf::Joystick::isButtonPressed(triggerPoint.device(), triggerPoint.code()))
                    {
                        sf::Event::JoystickButtonEvent event;
                        event.joystickId = triggerPoint.device();
                        event.button = triggerPoint.code();
                        
                        mData->mDetails.setJoystickButton(event);
                        ++mData->mTriggerPointMatches;
                    }
                    continue;
                }
            }
        }
        
        if (mData->mTriggerPointMatches == mData->mTriggerPoints.size())
        {
            mData->mEventMatchedEvent->signal(mData->mDetails);
        }
        
        mData->mTriggerPointMatches = 0;
        mData->mDetails.clear();
    }
    
private:
    struct TriggerData
    {
        std::string mName;
        EventDetails mDetails;
        TriggerPoints mTriggerPoints;
        unsigned int mTriggerPointMatches;
        std::shared_ptr<TriggerEvent> mEventMatchedEvent;
        
        TriggerData (const std::string & name)
        : mName(name), mDetails(name), mTriggerPointMatches(0), mEventMatchedEvent(new TriggerEvent())
        { }
        
        TriggerData (const TriggerData & src)
        : mName(src.mName), mDetails(src.mDetails), mTriggerPoints(src.mTriggerPoints),
        mTriggerPointMatches(src.mTriggerPointMatches), mEventMatchedEvent(src.mEventMatchedEvent)
        { }
        
        ~TriggerData ()
        { }
        
        TriggerData & operator = (const TriggerData & rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }
            
            mName = rhs.mName;
            mDetails = rhs.mDetails;
            mTriggerPoints = rhs.mTriggerPoints;
            mTriggerPointMatches = rhs.mTriggerPointMatches;
            mEventMatchedEvent = rhs.mEventMatchedEvent;
            
            return *this;
        }
    };
    
    std::unique_ptr<TriggerData> mData;
};
