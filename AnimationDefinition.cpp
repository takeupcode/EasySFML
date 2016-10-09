//
//  AnimationDefinition.cpp
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 10/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "SpriteSheet.h"

using namespace std;

FrameDefinition * AnimationDefinition::addFrame (const std::string & imageName, float time)
{
    const SpriteImage * image = mSheet->image(imageName);
    if (!image)
    {
        return nullptr;
    }
    
    mFrames.emplace_back(std::unique_ptr<FrameDefinition>(new FrameDefinition(time, image)));
    
    return mFrames[mFrames.size() - 1].get();
}
