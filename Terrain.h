//
//  Terrain.h
//  TankGame
//
//  Created by Jacob Gonzalez on 4/05/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef TERRAIN_H
#define TERRAIN_H

#include "View.h"
#include "MutableArray.h"

#define TERRAIN_DIRT 10
#define TERRAIN_ROCK 11

// :: view class handles all terrain tiles ::
// :: performs all destruction and generation ::
class Terrain : public View
{
public:
    // : default constructor :
    Terrain() : View()
    {
        _init();
    }
    ~Terrain()
    {}

    void update(int t);
    void draw();

    // : destroy all terrain in radius :
    // : returns true if hit anything :
    bool impact(Point<int> pos, int radius);

    // : return position of lowest tile at x :
    int get_floor(int x);

    // : get _wind_speed
    float get_wind_speed() const;
    // : set windspeed to a random value :
    void shuffle_wind_speed();

private:
    void _init();

    // : generate terrain height map into height_map
    void _gen_terrain(int start, int length, int *height_map);

    float _wind_speed;
};


#endif // TERRAIN_H
