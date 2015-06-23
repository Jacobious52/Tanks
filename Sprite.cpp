//
//  Sprite.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 4/05/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include "Sprite.h"
#include "StringTools.h"

// : get/set _fcolor :
ConsoleTools::Color Sprite::get_fcolor() const
{
    return _fcolor;
}

void Sprite::set_fcolor(ConsoleTools::Color color)
{
    _fcolor = color;
}

// : get/set _bcolor :
ConsoleTools::Color Sprite::get_bcolor() const
{
    return _bcolor;
}

void Sprite::set_bcolor(ConsoleTools::Color color)
{
    _bcolor = color;
}

// : getter/setter for _texture :
std::string Sprite::get_texture() const
{
    return _texture;
}

void Sprite::set_texture(std::string characters)
{
    _texture = characters;
}

void Sprite::update(int t)
{
    View::update(t);
}

// : draw funtion for all child views :
void Sprite::draw()
{
    vstring lines = StringTools::split(get_texture(), "\n");
    for (int i = 0; i < lines.get_count(); ++i)
    {
        // draw relative to parent
        Point<int> parent_pos;
        if (get_parent() != 0)
        {
            parent_pos = get_parent()->get_position();
        }
        else
        {
            parent_pos = Point<int>::zero();
        }

        // set position
        ConsoleTools::set_cursor(parent_pos.x + get_position().x, parent_pos.y + get_position().y + i);
        // set color
        ConsoleTools::set_color(get_fcolor(), get_bcolor());
        // draw
        printf("%s\n", lines[i].c_str());
        // end color
        ConsoleTools::end_color();
    }

    View::draw();
}
