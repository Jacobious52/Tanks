//
//  Terrian.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 4/05/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
#include "Terrain.h"
#include "Sprite.h"
#include "Timer.h"

void Terrain::_init()
{
    _size = ConsoleTools::get_terminal_size();
    _position = Point<int>::zero();

    shuffle_wind_speed();

    // create a array of terrain heights at every x pos
    int *height_map = new int[get_size().x];
    _gen_terrain(0, get_size().x, height_map);

    // fill in the map with sprites for every x pos
    for (int i = 0; i < get_size().x; ++i)
    {
        for (int h = get_size().y - height_map[i]; h < get_size().y; ++h)
        {
            Sprite *tile = new Sprite(" ");
            tile->set_position(Point<int>(i, h));
            if (h == get_size().y - 1)
            {
                tile->set_bcolor(ConsoleTools::white);
                tile->tag = TERRAIN_ROCK;
                tile->set_texture(" ");
            }
            else
            {
                tile->set_bcolor(ConsoleTools::green);
                tile->tag = TERRAIN_DIRT;
            }
            add_child(tile);
        }
    }

    delete[] height_map;
}

int Terrain::get_floor(int x)
{
    // the minimum y value is the top of the terrian
    int min = INT_MAX;
    LOOPV(i, this)
    {
        Point<int> tile_pos = get_child(i)->get_position();
        if (tile_pos.x == x && tile_pos.y < min)
        {
            min = tile_pos.y;
        }
    }
    return min;
}

bool Terrain::impact(Point<int> pos, int radius)
{
    int old_pos = _position.y;
    bool hit = false;

    // increment radius destruction in steps for animation
    for (int r = 2; r < radius; r+=2)
    {
        // pause for 0.05 seconds
        Timer timer(0.05, 1);
        while (timer.tick())
        {
            LOOPV(i, this)
            {
                // get the distance and add horrizontal stretch to look nicer
                Point<int> tile_pos = get_child(i)->get_position();
                Point<int> dist = tile_pos - pos;
                if (sqrt(pow(dist.x, 2) + pow(dist.y*2, 2)) < r)
                {
                    if (get_child(i)->tag == TERRAIN_DIRT)
                    {
                        delete get_children()->remove(i--);
                    }
                    hit = true;
                }
            }

            // for screen update for destruction animation
            ConsoleTools::clear_screen();
            _parent->draw();
        }
    }

    if (hit == true)
    {
        ConsoleTools::play_music("boom.wav");
    }

    _position.y = old_pos;

    return hit;
}

void Terrain::_gen_terrain(int start, int length, int *height_map)
{
    int amp = (rand() % get_size().y/5) + 5;
    int period = (rand() % 40) + 10;
    int height = (rand() % get_size().y/10) + 5;
    int phase = rand() % get_size().x;

    for (int i = start; i < length; ++i)
    {
        height_map[i] = std::abs(amp*sin(((float)i/(float)period) - phase) + height) + 5;
    }
}

void Terrain::shuffle_wind_speed()
{
    float wind = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
    int dir = rand() % 2;
    _wind_speed = dir == 0 ? -wind : wind;
}

float Terrain::get_wind_speed() const
{
    return _wind_speed;
}

void Terrain::update(int t)
{
    // update children
    LOOPV(i, this)
    {
        get_child(i)->update(t);
        if (get_child(i)->should_remove_from_parent() == true)
        {
            delete get_children()->remove(i);
            --i;
        }
    }
}

void Terrain::draw()
{
    // draw children
    LOOPV(i, this)
    {
        get_child(i)->draw();
    }
}
