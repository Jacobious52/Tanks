//
//  ConsoleTools.h
//  TankGame
//
//  Created by Jacob Gonzalez on 11/04/2015.
//  Copyright (c) 2015 Jacob Gonzalez. All rights reserved.
//

#ifndef _CONSOLE_TOOLS_H
#define _CONSOLE_TOOLS_H

#include "Point.h"
#include <cstdio>
#include <iostream>
#include <limits>
#include <string>
#include <fstream>

// :: Static utility class for accsess to all ANSI escape functions ::
class ConsoleTools
{
public:
    // enum for available console colors
    enum Color
    {
        black = 30,
        red = 31,
        green = 32,
        yellow = 33,
        blue = 34,
        magneta = 35,
        cyan = 36,
        white = 37,
        endc = 0
    };

    //enum for move cursor direction
    enum Direction
    {
        up = 'A',
        down = 'B',
        right = 'C',
        left = 'D'
    };

    // : gets input of type T :
    template <typename T>
    static T get_input(std::string error_message, Point<int> ret_pos)
    {
        T input;

        std::cin >> input;

        // repeat until valid imput entered
        while (std::cin.fail() == true)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // set back to original pos
            set_cursor(ret_pos);
            printf("%s", error_message.c_str());
            clear_line();
            std::cin >> input;
        }

        // clear the buffer
        std::cin.ignore();
        std::cin.clear();
        std::cin.sync();

        return input;
    }

    static std::string get_line();

    // : set the title of the terminal :
    static void set_title(char const *title);

    // : set the forground color of the terminal :
    static void set_fcolor(Color color);
    // : set the background color of the terminal :
    static void set_bcolor(Color color);
    // : set front and back color of terminal :
    static void set_color(Color fcolor, Color bcolor);
    // : end colors :
    static void end_color();

    // : hide text :
    // : turned off using end_color() :
    static void hide_text();

    // : reverses forground and background color :
    // : end with end_color() :
    static void reverse_color();

    // : clear entire screen :
    static void clear_screen();
    // : clear current line :
    static void clear_line();

    // : sets position of cursor to x, y :
    static void set_cursor(int x, int y);
    static void set_cursor(Point<int> pos);
    // : moves cursor in the direction dir dist rows/cols
    static void move_cursor(Direction dir, int dist);

    // : get size of terminal as Point<T> x=cols,y=rows :
    static Point<int> get_terminal_size();

    static void play_music(std::string filename);
    static void stop_music();

    // : static flags for audio and replay :
    static bool audio;
    static bool replay;
};

#endif /* _CONSOLE_TOOLS_H */
