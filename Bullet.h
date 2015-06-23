//
//  Bullet.h
//  TankGame
//
//  Created by Jacob Gonzalez on 4/05/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef BULLET_H
#define BULLET_H

#include "Sprite.h"
#include "Terrain.h"

// :: bullet class handles all tank bullet logic ::
// :: bullet handles terrain destruction and terrain impact
// :: does not handle tank impact ::
class Bullet : public Sprite
{
public:
    Bullet(Point<int> start, float angle, float power, Terrain *terrain)
        : Sprite("*"),
        _angle(angle), _power(power)
    {
        _terrain = terrain;
         _position = start;
         _start_pos = _position;
        _init();
    }
    ~Bullet()
    {}

    // : reset and allow update :
    void fire();

    //  : return _laucnhed
    bool get_launched() const;

    void update(int t);
    void draw();

private:
    Point<float> _velocity;
    float _angle;
    float _power;

    bool _launched;
    Point<int> _start_pos;

    Terrain *_terrain;

    void _init();
};

#endif // BULLET_H
