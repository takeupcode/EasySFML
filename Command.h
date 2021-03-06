//
//  Command.h
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

class Command
{
public:
    virtual ~Command () = default;
    
    virtual void execute () = 0;
    virtual void undo () = 0;
};
