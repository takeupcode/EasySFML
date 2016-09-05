//
//  SceneManager.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include <memory>
#include <vector>

#include "Director.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Window.h"

using namespace std;

SceneManager::SceneManager (Director * director)
: Directable(director), mFirstScene(nullptr)
{ }

bool SceneManager::hasScene (int scene) const
{
    Scene * currentScene = mFirstScene;
    while (currentScene)
    {
        if (currentScene->identity() == scene)
        {
            for (auto & identity: mScenesToBeRemoved)
            {
                if (identity == scene)
                {
                    return false;
                }
            }
            return true;
        }
        currentScene = currentScene->mNextScene;
    }
    
    return false;
}

int SceneManager::currentScene () const
{
    if (mFirstScene)
    {
        return mFirstScene->identity();
    }
    
    return 0;
}

bool SceneManager::addScene (int scene, bool addToFront)
{
    for (auto position = mScenesToBeRemoved.begin(); position != mScenesToBeRemoved.end(); ++position)
    {
        if (*position == scene)
        {
            mScenesToBeRemoved.erase(position);
        }
    }
    if (addToFront && mFirstScene && mFirstScene->identity() != scene)
    {
        mFirstScene->deactivated();
    }
    
    Scene * currentScene = mFirstScene;
    while (currentScene)
    {
        if (currentScene->identity() == scene)
        {
            if (!addToFront)
            {
                return true;
            }
            
            if (currentScene->mNextScene && currentScene->mPreviousScene)
            {
                currentScene->mNextScene->mPreviousScene = currentScene->mPreviousScene;
                currentScene->mPreviousScene->mNextScene = currentScene->mNextScene;
            }
            else if (currentScene->mPreviousScene)
            {
                currentScene->mPreviousScene->mNextScene = nullptr;
            }
            else
            {
                // The scene is already the most active scene.
                return true;
            }
            
            currentScene->mNextScene = mFirstScene;
            currentScene->mPreviousScene = nullptr;
            
            mFirstScene->mPreviousScene = currentScene;
            mFirstScene = currentScene;
            
            mFirstScene->activated();
            
            return true;
        }
        currentScene = currentScene->mNextScene;
    }
    
    Scene * newScene = mRegisteredScenes[scene].get();
    if (addToFront)
    {
        newScene->mNextScene = mFirstScene;
        newScene->mPreviousScene = nullptr;
        
        if (mFirstScene)
        {
            mFirstScene->mPreviousScene = newScene;
        }
        mFirstScene = newScene;
        mFirstScene->created();
        mFirstScene->activated();
    }
    else
    {
        Scene * lastScene = mFirstScene;
        while (lastScene && lastScene->mNextScene)
        {
            lastScene = lastScene->mNextScene;
        }
        newScene->mNextScene = nullptr;
        newScene->mPreviousScene = lastScene;
        
        if (lastScene)
        {
            lastScene->mNextScene = newScene;
            newScene->created();
        }
        else
        {
            mFirstScene = newScene;
            mFirstScene->created();
            mFirstScene->activated();
        }
    }
    
    return true;
}

bool SceneManager::removeScene (int scene)
{
    if (hasScene(scene))
    {
        mScenesToBeRemoved.push_back(scene);
        return true;
    }
    return false;
}

void SceneManager::processSceneRemovals ()
{
    for (auto & identity: mScenesToBeRemoved)
    {
        Scene * currentScene = mFirstScene;
        while (currentScene)
        {
            if (currentScene->identity() == identity)
            {
                if (currentScene == mFirstScene)
                {
                    currentScene->deactivated();
                }
                
                if (currentScene->mNextScene && currentScene->mPreviousScene)
                {
                    currentScene->mNextScene->mPreviousScene = currentScene->mPreviousScene;
                    currentScene->mPreviousScene->mNextScene = currentScene->mNextScene;
                }
                else if (currentScene->mPreviousScene)
                {
                    currentScene->mPreviousScene->mNextScene = nullptr;
                }
                else
                {
                    currentScene->mNextScene->mPreviousScene = nullptr;
                    
                    mFirstScene = currentScene->mNextScene;
                    
                    mFirstScene->activated();
                }
                
                currentScene->destroyed();
                break;
            }
            currentScene = currentScene->mNextScene;
        }
    }
}

void SceneManager::update (float elapsedSeconds)
{
    Scene * currentScene = mFirstScene;
    if (!currentScene)
    {
        return;
    }
    while (!currentScene->isModal() && currentScene->mNextScene)
    {
        currentScene = currentScene->mNextScene;
    }
    
    while (currentScene)
    {
        currentScene->update(elapsedSeconds);
        currentScene = currentScene->mPreviousScene;
    }
}

void SceneManager::render ()
{
    Scene * currentScene = mFirstScene;
    if (!currentScene)
    {
        return;
    }
    while (currentScene->isTransparent() && currentScene->mNextScene)
    {
        currentScene = currentScene->mNextScene;
    }
    
    vector<shared_ptr<Window>> windowsToBeRendered;
    while (currentScene)
    {
        bool newWindow = true;
        for (auto & window: windowsToBeRendered)
        {
            if (window->identity() == currentScene->mWindow->identity())
            {
                newWindow = false;
                break;
            }
        }
        if (newWindow)
        {
            windowsToBeRendered.push_back(currentScene->mWindow);
            currentScene->mWindow->drawBegin();
        }
        currentScene->mWindow->setView(currentScene->view());
        currentScene->render();
        currentScene = currentScene->mPreviousScene;
    }
    
    for (auto & window: windowsToBeRendered)
    {
        window->drawEnd();
    }
}

void SceneManager::notify (EventParameter eventDetails)
{
    
}

void SceneManager::loadTriggers ()
{
    
}
