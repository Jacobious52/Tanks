//
//  GameView.h
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "View.h"
#include "Sprite.h"
#include "Terrain.h"
#include "Tank.h"
#include "Bullet.h"
#include "DebugView.h"

// :: Main game view ::
// :: All main game logic and drawing happens here
class GameView : public View
{
public:
    // : constructor with names of players :
    GameView(std::string name1, std::string name2) : View()
    {
        _init(name1, name2);
    }
    ~GameView()
    {}

    void update(int t);
    void draw();

    // : getter for winner of game :
    // : used by EndView
    std::string get_winner() const;

private:
    void _init(std::string name1, std::string name2);

    void _get_input();

    Terrain *_terrain;

    //DebugView *_debug_view;

    Tank *_tank1;
    Tank *_tank2;
    Bullet *_bullet;
    Sprite *_input_box;

    // : turn of player :
    // : let false be player1
    // : let true be player2
    bool turn;
    std::string _winner;
};

#endif // GAME_VIEW_H
