//
//  Tank.h
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include "Tank.h"
#include "Timer.h"

#define GRAVITY 2

void Tank::_init()
{
    // add a name above the tank
    Sprite *name_plate = new Sprite(_name);
    name_plate->set_position(Point<int>(-name_plate->get_size().x/4, -2));
    name_plate->set_fcolor(_fcolor);
    name_plate->set_bcolor(ConsoleTools::white);
    add_child(name_plate);
}

std::string Tank::get_name() const
{
    return _name;
}

void Tank::update(int t)
{
    Sprite::update(t);
}

void Tank::draw()
{
    Sprite::draw();
}
