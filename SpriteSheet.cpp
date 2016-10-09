//
//  SpriteSheet.cpp
//  EasySFML
//
//  Created by Abdul Wahid Tanner on 10/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "SpriteSheet.h"

using namespace std;
namespace pt = boost::property_tree;

SpriteSheet::SpriteSheet (const string & name, const string & dataFileName, const shared_ptr<sf::Texture> & texture)
: mName(name), mTexture(texture)
{
    pt::ptree tree;
    pt::read_json(dataFileName, tree);
    
    for (pt::ptree::value_type & frame: tree.get_child("frames"))
    {
        string name = frame.second.get<string>("filename");
        unsigned int sheetX = frame.second.get<unsigned int>("frame.x");
        unsigned int sheetY = frame.second.get<unsigned int>("frame.y");
        unsigned int sheetWidth = frame.second.get<unsigned int>("frame.w");
        unsigned int sheetHeight = frame.second.get<unsigned int>("frame.h");
        unsigned int sourceX = frame.second.get<unsigned int>("spriteSourceSize.x");
        unsigned int sourceY = frame.second.get<unsigned int>("spriteSourceSize.y");
        unsigned int sourceWidth = frame.second.get<unsigned int>("sourceSize.w");
        unsigned int sourceHeight = frame.second.get<unsigned int>("sourceSize.h");
        bool rotated = frame.second.get<bool>("rotated");
        bool trimmed = frame.second.get<bool>("trimmed");
        
        mImages.emplace(name, std::unique_ptr<SpriteImage>(new SpriteImage({sheetX, sheetY}, {sheetWidth, sheetHeight}, {sourceX, sourceY}, {sourceWidth, sourceHeight}, rotated, trimmed)));
    }
}
