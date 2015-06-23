//
//  Sprite.h
//  TankGame
//
//  Created by Jacob Gonzalez on 4/05/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef SPRITE_H
#define SPRITE_H

#include "View.h"
#include "ConsoleTools.h"
#include "StringTools.h"
#include <string>

// :: Sprite class handles all drawing of sprites ::
class Sprite : public View
{
public:
    // : default contructor :
    Sprite()
        : View(),
         _fcolor(ConsoleTools::endc),
        _bcolor(ConsoleTools::endc)
    {}

    // : position, size contructor
    Sprite(Point<int> pos, Point<int> size)
        : View(pos, size),
        _fcolor(ConsoleTools::endc),
        _bcolor(ConsoleTools::endc)
    {}

    // : pos: x, y, size: w, h contructor
    Sprite(int x, int y, int w, int h)
        : View(x, y, w, h),
        _fcolor(ConsoleTools::endc),
        _bcolor(ConsoleTools::endc)
    {}

    // : init with text file :
    // : auto set size based on string :
    Sprite(std::string texture)
        : View(),
        _fcolor(ConsoleTools::endc),
        _bcolor(ConsoleTools::endc)
    {
        _texture = texture;
        _position = Point<int>::zero();
        _size = StringTools::string_size(_texture);
    }

    virtual ~Sprite()
    {}

    // : getter/setter for _texture :
    std::string get_texture() const;
    void set_texture(std::string characters);

    // : update funtion for all child views :
    virtual void update(int t);

    // : draw funtion for all child views :
    virtual void draw();

    // : get/set _fcolor :
    ConsoleTools::Color get_fcolor() const;
    void set_fcolor(ConsoleTools::Color color);

    // : get/set _bcolor :
    ConsoleTools::Color get_bcolor() const;
    void set_bcolor(ConsoleTools::Color color);

protected:
    // : text that is printed to screen
    std::string _texture;

    // : foreground and background color
    ConsoleTools::Color _fcolor;
    ConsoleTools::Color _bcolor;
};

#endif  // SPRITE_H
