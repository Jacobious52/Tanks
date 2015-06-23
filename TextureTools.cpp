//
//  TextureTools.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include "TextureTools.h"

// : init static map
std::map<std::string, std::string> TextureTools::_texture_map = _init_map();

std::map<std::string, std::string> TextureTools::_init_map()
{
    std::map<std::string, std::string> map;
    // add a hard coded test value
    map["debug"] = "___________\n***DEBUG***\n-----------";
    return map;
}

bool TextureTools::load_texture_file(std::string filename)
{
    std::string text = StringTools::readall(filename);

    if (text == "$NO FILE")
    {
        return false;
    }

    // put file into map by spliting at "
    vstring textures = StringTools::tokens(text, "\"");

    for (int i = 0; i < textures.get_count(); i+=2)
    {
        std::string key = textures[i];
        std::string texture = StringTools::trim(textures[i + 1], "\n");

        _texture_map[key] = texture;
    }

    return true;
}

std::string TextureTools::get_texture(std::string key)
{
    if (_texture_map.find(key) != _texture_map.end())
    {
        return _texture_map[key];
    }
    else
    {
        return "$NO KEY";
    }
}
