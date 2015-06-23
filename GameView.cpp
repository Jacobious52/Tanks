//
//  GameView.cpp
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#include <cstdio>
#include "GameView.h"
#include "TextureTools.h"
#include "Sprite.h"
#include <fstream>

#define MIN(ARG_1, ARG_2) ARG_1 < ARG_2 == true ? ARG_1 : ARG_2

void GameView::_init(std::string name1, std::string name2)
{
    ConsoleTools::clear_screen();

    add_child(DebugView::shared_view());

    _position = Point<int>::zero();
    _size = ConsoleTools::get_terminal_size();

    // create tebrrain
    _terrain = new Terrain();
    add_child(_terrain);

    turn = false;

    // create tank 1
    int spawn_x = (rand() % 20) + 5;
    _tank1 = new Tank(name1, TextureTools::get_texture("tank1"), ConsoleTools::red);
    _tank1->set_position(Point<int>(spawn_x, _terrain->get_floor(spawn_x) - _tank1->get_size().y));
    add_child(_tank1);

    // create base for tank 1
    Sprite *base1 = new Sprite("        ");
    base1->set_position(_tank1->get_position() + Point<int>(-2, _tank1->get_size().y));
    base1->set_bcolor(ConsoleTools::white);
    base1->tag = TERRAIN_ROCK;
    _terrain->add_child(base1);

    // create tank 2
    spawn_x = (rand() % 20) + 5;
    _tank2 = new Tank(name2, TextureTools::get_texture("tank2"), ConsoleTools::blue);
    _tank2->set_position(Point<int>(get_size().x - spawn_x, _terrain->get_floor(get_size().x - spawn_x) - _tank2->get_size().y));
    add_child(_tank2);

    // create base for tank 2
    Sprite *base2 = new Sprite("        ");
    base2->set_position(_tank2->get_position() + Point<int>(-1, _tank2->get_size().y));
    base2->set_bcolor(ConsoleTools::white);
    base2->tag = TERRAIN_ROCK;
    _terrain->add_child(base2);

    // create box for input
    _input_box = new Sprite(TextureTools::get_texture("input"));
    _input_box->set_position(Point<int>(get_size().x/2 - _input_box->get_size().x/8, 3));
    _input_box->set_bcolor(ConsoleTools::endc);
    _input_box->set_fcolor(ConsoleTools::magneta);

    // create bullet, don't fire
    _bullet = new Bullet(_tank1->get_position(), 0, 0, _terrain);
    add_child(_bullet);
}

void GameView::_get_input()
{
    // choose tank depending on turn
    Tank *current_tank = (turn == false) ? _tank1 : _tank2;
    float angle_offset = (turn == false) ? 0: M_PI;
    turn = !turn;

    _input_box->draw();

    // draw tank name
    ConsoleTools::set_color(current_tank->get_fcolor(), ConsoleTools::endc);
    ConsoleTools::set_cursor(_input_box->get_position().x + 1, _input_box->get_position().y + 1);
    printf("%s", current_tank->get_name().c_str());

    // draw input text stuff
    ConsoleTools::set_cursor(_input_box->get_position().x + 1, _input_box->get_position().y + 3);
    printf("power: ");
    ConsoleTools::set_cursor(_input_box->get_position().x + 1, _input_box->get_position().y + 4);
    printf("angle: ");

    // write to input file
    if (DebugView::shared_view()->show == true)
    {
        std::ofstream file("computer.txt", std::ios::app);
        file << (rand() % 7) + 1 << " " << (rand() % 80) << std::endl;
        file.close();
    }

    // get power input
    ConsoleTools::move_cursor(ConsoleTools::up, 1);
    float p = ConsoleTools::get_input<float>("float! ",
        Point<int>(_input_box->get_position().x + 1, _input_box->get_position().y + 3));
    ConsoleTools::play_music("beep.wav");

    // get angle input
    ConsoleTools::set_cursor(_input_box->get_position().x + StringTools::string_width("angle: ") + 1, _input_box->get_position().y + 4);
    float a = ConsoleTools::get_input<float>("float! ",
        Point<int>(_input_box->get_position().x + 1, _input_box->get_position().y + 4));

    // write power and angle to replay file
    if (ConsoleTools::replay == false)
    {
        std::ofstream file("replay.txt", std::ios::app);
        file << p << " " << a << std::endl;
        file.close();
    }

    DebugView::shared_view()->watch("power", p);
    DebugView::shared_view()->watch("angle", a);

    if (a == -1 && p == -1)
    {
        _should_remove_from_parent = true;
        return;
    }

    // create new bulelt and fire
    // bullet already deleted by update loop
    _bullet = new Bullet(current_tank->get_position(), std::abs(angle_offset - a*(M_PI/180)), MIN(p, 10.0), _terrain);
    _bullet->fire();
    add_child(_bullet);
}

void GameView::update(int t)
{
    // bullet needs firing
    DebugView::shared_view()->watch("terrain count", _terrain->get_children()->get_count());

    View::update(t);

    // check if bullet is inside tank1
    if (_bullet->get_position().x >= _tank1->get_position().x
        && _bullet->get_position().x <= _tank1->get_position().x + _tank1->get_size().x
        && _bullet->get_position().y > _tank1->get_position().y
        && _bullet->get_position().y <= _tank1->get_position().y + _tank1->get_size().y)
    {
        _winner = _tank2->get_name();
        ConsoleTools::play_music("boom.wav");
        _should_remove_from_parent = true;
        return;
    }
    // check if bullet is inside tank2
    else if (_bullet->get_position().x >= _tank2->get_position().x
        && _bullet->get_position().x <= _tank2->get_position().x + _tank2->get_size().x
        && _bullet->get_position().y > _tank2->get_position().y
        && _bullet->get_position().y <= _tank2->get_position().y + _tank2->get_size().y)
    {
        _winner = _tank1->get_name();
        ConsoleTools::play_music("boom.wav");
        _should_remove_from_parent = true;
        return;
    }
    // bullet has hit. next turn
    if (_bullet->get_launched() == false || _bullet->should_remove_from_parent() == true)
    {
        _terrain->shuffle_wind_speed();
        DebugView::shared_view()->watch("wind speed", _terrain->get_wind_speed());
        draw();
       _get_input();
    }
}

void GameView::draw()
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

    //clear top line
    ConsoleTools::set_cursor(0, 1);
    ConsoleTools::clear_line();
    // print wind speed arrows
    ConsoleTools::set_fcolor(ConsoleTools::cyan);
    for (int i = 0; i < std::abs(_terrain->get_wind_speed()*10); ++i)
    {
        ConsoleTools::set_cursor(get_size().x/2 - 5 + i, 1);
        if (_terrain->get_wind_speed() > 0)
        {
            printf(">");
        }
        else if (_terrain->get_wind_speed() < 0)
        {
            printf("<");
        }
    }
    ConsoleTools::end_color();

    // draw children
    View::draw();
}

std::string GameView::get_winner() const
{
    return _winner;
}
