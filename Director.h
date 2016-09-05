//
//  Director.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/2/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>

class Game;
class EventManager;
class SceneManager;
class TextureManager;
class WindowManager;

class Director
{
public:
    Director ()
    { }
    
    ~Director ()
    { }
    
    void playGame ();

    std::shared_ptr<Game> game () const
    {
        return mGame;
    }
    
    void setGame (std::shared_ptr<Game> game);
    
    std::shared_ptr<EventManager> eventManager () const
    {
        return mEventManager;
    }
    
    void setEventManager (std::shared_ptr<EventManager> manager);
    
    std::shared_ptr<SceneManager> sceneManager () const
    {
        return mSceneManager;
    }
    
    void setSceneManager (std::shared_ptr<SceneManager> manager);
    
    std::shared_ptr<TextureManager> textureManager () const
    {
        return mTextureManager;
    }
    
    void setTextureManager (std::shared_ptr<TextureManager> manager);
    
    std::shared_ptr<WindowManager> windowManager () const
    {
        return mWindowManager;
    }
    
    void setWindowManager (std::shared_ptr<WindowManager> manager);
    
private:
    void loadTriggers ();
    
    void onConfigurationChange ();
    
    Director (const Director & src) = delete;
    Director & operator = (const Director & rhs) = delete;
    
    std::shared_ptr<Game> mGame;
    std::shared_ptr<EventManager> mEventManager;
    std::shared_ptr<SceneManager> mSceneManager;
    std::shared_ptr<TextureManager> mTextureManager;
    std::shared_ptr<WindowManager> mWindowManager;
};
