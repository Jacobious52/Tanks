//
//  IntroView.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include "IntroView.h"
#include "TextureTools.h"
#include "ConsoleTools.h"
#include "Point.h"
#include "Terrain.h"
#include <cstdlib>

void IntroView::_init()
{
    player1 = "";
    player2 = "";

    _position = Point<int>::zero();
    _size = ConsoleTools::get_terminal_size();

    // title
    Sprite *header = new Sprite(TextureTools::get_texture("title"));
    // adjust positions for unicode text
    header->set_position(Point<int>(get_size().x/2 - header->get_size().x/4 - 6, 2));
    header->set_size(Point<int>(header->get_size().x, header->get_size().y));
    header->set_fcolor(ConsoleTools::magneta);
    header->tag = 1;

    add_child(header);

     // copyright
    Sprite *copyright = new Sprite("Copyright © Jacob Gonzalez (a1687803) 2015");
    copyright->set_position(Point<int>(get_size().x/2 - copyright->get_size().x/2,
                                         get_size().y - 1));
    copyright->set_fcolor(ConsoleTools::green);

    add_child(copyright);

    // vs_text. not adding to view for can be on stack

    _vs_text = Sprite(TextureTools::get_texture("vs"));
    _vs_text.set_position(Point<int>(get_size().x/2 - _vs_text.get_size().x/4 + 2,
                                        get_size().y/2 - _vs_text.get_size().y/2));
    _vs_text.set_fcolor(ConsoleTools::yellow);

    // loading string
    _load_num_string = "";
}

void IntroView::update(int t)
{
    // get player's name's after sometime
    if (t == 20 && player1 == "" && player2 == "")
    {
        ConsoleTools::set_cursor(0, get_size().y/2);
        ConsoleTools::clear_line();

        // get player 1
        ConsoleTools::set_cursor(get_size().x/2 - StringTools::string_width("Name of Player 1")/2, get_size().y/3);
        ConsoleTools::set_fcolor(ConsoleTools::white);
        printf("Name of Player 1");
        ConsoleTools::move_cursor(ConsoleTools::down, 2);
        ConsoleTools::move_cursor(ConsoleTools::left, StringTools::string_width("Name of Player 1"));
        ConsoleTools::set_fcolor(ConsoleTools::red);
        player1 = ConsoleTools::get_line();
        ConsoleTools::play_music("beep.wav");

        // get player 2
        ConsoleTools::set_cursor(get_size().x/2 - StringTools::string_width("Name of Player 2")/2, 2*get_size().y/3);
        ConsoleTools::set_fcolor(ConsoleTools::white);
        printf("Name of Player 2");
        ConsoleTools::move_cursor(ConsoleTools::down, 2);
        ConsoleTools::move_cursor(ConsoleTools::left, StringTools::string_width("Name of Player 2"));
        ConsoleTools::set_fcolor(ConsoleTools::blue);
        player2 = ConsoleTools::get_line();
        ConsoleTools::play_music("beep.wav");

        // write to replay file
        if (ConsoleTools::replay == false)
        {
            std::ofstream file("replay.txt", std::ios::app);
            file << player1 << std::endl << player2 << std::endl;
            file.close();
        }

    }
    else if (t < 20 && t % 4 == 0)
    {
        // increment the loader
        if (_load_num_string == "")
        {
            _load_num_string = ".";
        }
        else if (_load_num_string == ".")
        {
            _load_num_string = "..";
        }
        else if (_load_num_string == "..")
        {
            _load_num_string = "...";
        }
        else if (_load_num_string == "...")
        {
            _load_num_string = "";
        }
    }
    else if (t > 60)
    {
        _should_remove_from_parent = true;
    }

    // update children
    View::update(t);
}

void IntroView::draw()
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

    if (player1 != "" && player2 != "")
    {
        // draw player vs info
        ConsoleTools::set_cursor(get_size().x/2 - StringTools::string_width(player1)/2, get_size().y/3);
        ConsoleTools::set_fcolor(ConsoleTools::red);
        printf("%s", player1.c_str());

        _vs_text.draw();

        ConsoleTools::set_cursor(get_size().x/2 - StringTools::string_width(player2)/2, 2*get_size().y/3);
        ConsoleTools::set_fcolor(ConsoleTools::blue);
        printf("%s", player2.c_str());
    }
    else
    {
        // draw the loading text
        ConsoleTools::set_cursor(get_size().x/2 - (18 + StringTools::string_width(_load_num_string))/2, get_size().y/2);
        ConsoleTools::set_fcolor(ConsoleTools::yellow);
        ConsoleTools::clear_line();
        printf("Pretending to load%s", _load_num_string.c_str());
    }

    // draw children
    View::draw();
}
