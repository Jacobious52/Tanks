//
//  Bullet.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 4/05/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include <cmath>
#include "Bullet.h"
#include "ConsoleTools.h"
#include "TextureTools.h"
#include "Terrain.h"
#include "DebugView.h"

#define GRAVITY 2

void Bullet::_init()
{
    _fcolor = ConsoleTools::yellow;
    // set inital velocity
    _velocity = Point<float>(_power*cosf(_angle), -_power*std::abs(sinf(_angle)));
    _launched = false;
}

void Bullet::fire()
{
    _init();
    _launched = true;
    _position = _start_pos;
    ConsoleTools::play_music("fire.wav");
}

bool Bullet::get_launched() const
{
    return _launched;
}

void Bullet::update(int t)
{
    // don't update unless launched
    if (_launched == false)
    {
        return;
    }

    // increment velocity and position
    // vel += (gravity + wind) * slowdownfactor
    // pos += vel
    _velocity = _velocity + (Point<float>(0, GRAVITY) + Point<float>(_terrain->get_wind_speed(), 0)) * Point<float>(0.1, 0.1);
    _position = Point<int>(static_cast<int>(_position.x + _velocity.x), static_cast<int>(_position.y + _velocity.y));

    // remove if outside of view
    if (_position.y >= _terrain->get_size().y
        || _position.x >= _terrain->get_size().x
        || _position.x <= 0)
    {
        _should_remove_from_parent = true;
    }
    else if (_position.y <= 0)
    {
        // show ^ for above screen
        _position.y = 0;
        _texture = "^";
    }
    else
    {
        // going left to right
        if (_velocity.x > 0.5)
        {
            // going down
            if (_velocity.y > 0.5)
            {
                DebugView::shared_view()->watch("direction", 1);
                _texture = TextureTools::get_texture("bullet_down");
            }
            else if (_velocity.y < -0.5)
            {
                // going up
                DebugView::shared_view()->watch("direction", 2);
                _texture = TextureTools::get_texture("bullet_up");
            }
            else
            {
                // going horrizontal
                DebugView::shared_view()->watch("direction", 3);
                _texture = TextureTools::get_texture("bullet_flat");
            }
        }
        else if (_velocity.x < -0.5)
        {
            if (_velocity.y > 0.5)
            {
                // going down
                DebugView::shared_view()->watch("direction", 4);
                _texture = TextureTools::get_texture("bullet_up");
            }
            else if (_velocity.y < -0.5)
            {
                // going up
                DebugView::shared_view()->watch("direction", 5);
                _texture = TextureTools::get_texture("bullet_down");
            }
            else
            {
                // horizontal
                DebugView::shared_view()->watch("direction", 6);
                _texture = TextureTools::get_texture("bullet_flat");
            }
        }
        else
        {
            // vertical
            DebugView::shared_view()->watch("direction", 0);
            _texture = TextureTools::get_texture("bullet_vert");
        }

        LOOPV(i, _terrain)
        {
            if (_position.y >= _terrain->get_floor(_position.x))
            {
                // bullet hit ground.. remove it
                _position.y = _terrain->get_floor(_position.x);
                if (_terrain->impact(Point<int>(_position.x, _terrain->get_floor(_position.x)), 10))
                {
                    DebugView::shared_view()->watch("impact x", _position.x);
                    DebugView::shared_view()->watch("impact y", _terrain->get_floor(_position.x));
                    _should_remove_from_parent = true;
                }
            }
        }
    }

    // update debug watch vars
    DebugView::shared_view()->watch("bullet pos x ", static_cast<float>(get_position().x));
    DebugView::shared_view()->watch("bullet pos y ", static_cast<float>(get_position().y));
    DebugView::shared_view()->watch("bullet vel x ", _velocity.x);
    DebugView::shared_view()->watch("bullet vel y ", _velocity.y);

    Sprite::update(t);
}

void Bullet::draw()
{
    if (_launched == false)
    {
        return;
    }

    Sprite::draw();
}
