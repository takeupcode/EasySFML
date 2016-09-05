//
//  Directable.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <stdexcept>

class Director;

class Directable
{
protected:
    friend class Director;
    
    explicit Directable (Director * director)
    : mDirector(director)
    { }
    
    Directable (const Directable & src)
    : mDirector(src.mDirector)
    { }
    
    Directable (Directable && src)
    : mDirector(src.mDirector)
    { }
    
    virtual ~Directable ()
    { }
    
    Directable & operator = (const Directable & rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        
        mDirector = rhs.mDirector;
        
        return *this;
    }

    Director * director () const
    {
        if (!mDirector)
        {
            throw new std::logic_error("Director not set.");
        }
        
        return mDirector;
    }
    
private:
    // The Director pointer does not need to be deleted and can be copied.
    Director * mDirector;
};
