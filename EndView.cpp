//
//  EndView.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 4/05/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include "EndView.h"
#include "Sprite.h"
#include "ConsoleTools.h"
#include "TextureTools.h"
#include "StringTools.h"
#include <cstdio>

void EndView::_init()
{
    _position = Point<int>::zero();
    _size = ConsoleTools::get_terminal_size();

    // game over text
    Sprite *game_over_text = new Sprite(TextureTools::get_texture("gameover"));
    game_over_text->set_position(Point<int>(get_size().x/2 - game_over_text->get_size().x/4 + 6, 2));
    game_over_text->set_size(Point<int>(game_over_text->get_size().x, game_over_text->get_size().y));
    game_over_text->set_fcolor(ConsoleTools::magneta);
    add_child(game_over_text);

    // winner name text
    Sprite *winner_text = new Sprite(_winner + " Wins!");
    winner_text->set_position(Point<int>(_size.x/2 - StringTools::string_width(_winner + " Wins!")/2, (_size.y/2)-1));
    winner_text->set_fcolor(ConsoleTools::magneta);
    winner_text->set_bcolor(ConsoleTools::white);
    add_child(winner_text);
}

void EndView::update(int t)
{
    // exit after 60 ticks
    if (t > 60)
    {
        _should_remove_from_parent = true;
    }

    View::update(t);
}

void EndView::draw()
{
    // draw rain
    if (tag == 1)
    {
        for (int i = 0; i < get_size().x; i+=5)
        {
            ConsoleTools::set_fcolor(ConsoleTools::cyan);
            ConsoleTools::set_cursor(Point<int>(i, rand() % get_size().y));
            printf("|");
        }
    }

    // draw children
    View::draw();
}
