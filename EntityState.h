//
//  EntityState.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 10/9/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

class EntityState
{
public:
    virtual ~EntityState () = default;
    
    virtual bool handleCommand (int command) = 0;
    virtual void update (float elapsedSeconds) = 0;
    
    virtual void enter ()
    { }
    
    virtual void exit ()
    { }
};
