//
//  TextureTools.h
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef TEXTURE_TOOLS_H
#define TEXTURE_TOOLS_H

#include "StringTools.h"
#include <cstdio>
#include <ctime>
#include <fstream>
#include <map>

// :: static utility class for loading and getting textures ::
// :: Todo: turn into singleton Textures class? ::
class TextureTools
{
public:
    // : loads a texture map file into the _texture_map :
    static bool load_texture_file(std::string filename);

    // : gets the texture for a key :
    static std::string get_texture(std::string key);

private:
    // : static texture map :
    static std::map<std::string, std::string> _texture_map;

    // : for initing the map :
    static std::map<std::string, std::string> _init_map();
};

#endif // TEXTURE_TOOLS_H
