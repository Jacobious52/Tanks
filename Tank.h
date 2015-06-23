//
//  Tank.h
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef TANK_H
#define TANK_H

#include "Sprite.h"
#include "Terrain.h"

// :: tank class to control all logic and subviews of a tank ::
class Tank : public Sprite
{
public:
    // contructor to set name, texture and color
    Tank(std::string name, std::string texture, ConsoleTools::Color color)
        : Sprite(texture), _name(name)
    {
        _fcolor = color;
        _init();
    }
    ~Tank()
    {}

    void update(int t);
    void draw();

    // : getter for name of player for tank :
    std::string get_name() const;

private:
    void _init();
    std::string _name;
};

#endif // TANK_H
